#include "pch.h"
#include "CLevelSaveLoad.h"

#include <Engine/CPathMgr.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>
#include <Engine/components.h>
#include <Engine/CAssetMgr.h>

#include <Scripts/CScriptMgr.h>
#include <Engine/CScript.h>


void CLevelSaveLoad::SaveLevel(CLevel* _Level, const wstring& _strLevelPath)
{
	assert(_Level);
	assert(LEVEL_STATE::STOP == _Level->GetState() || LEVEL_STATE::NONE == _Level->GetState());

	// Level �� ������ ���
	wstring strLevelPath = CPathMgr::GetContentPath();
	strLevelPath += _strLevelPath;

	ofstream savelv;
	savelv.open(strLevelPath, std::ios::trunc);

	if (savelv.is_open())
	{
		savelv << strLevelPath << endl;
		for (UINT i = 0; i < LAYER_MAX; ++i)
		{
			SaveLayer(_Level->GetLayer(i), savelv);
		}
	}
}

void CLevelSaveLoad::SaveLayer(CLayer* _Layer, ofstream&_savelayer)
{
	// Layer �� �̸� ����
	if(_Layer->GetName() == "")
	{
		string num;
		_savelayer << to_string (_Layer->GetLayerIdx()) << endl;

	}
	else
	_savelayer << _Layer->GetName() << endl;


	// Layer �� �����ϰ� �ִ� GameObject ���� ����
	const vector<CGameObject*>& vecObject = _Layer->GetParentObjects();

	size_t ObjCount = vecObject.size();

	_savelayer << ObjCount << endl;

	for (size_t i = 0; i < vecObject.size(); ++i)
	{
		SaveGameObject(vecObject[i], _savelayer);
	}	
}

void CLevelSaveLoad::SaveGameObject(CGameObject* _Obj, ofstream& _saveobj)
{
	// GameObject �� �̸��� ����
	_saveobj << _Obj->GetName() << endl;

	// obj�� ���̾ ����
	int ObjLayerNum = 0;
	ObjLayerNum = _Obj->GetLayerIdx();

	_saveobj << ObjLayerNum << endl;

	// ������Ʈ ������ ����
	UINT i = 0;
	for ( ; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		CComponent* pCom = _Obj->GetComponent((COMPONENT_TYPE)i);
		if (nullptr == pCom)
			continue;

		// ������Ʈ Ÿ�� ���� ����

		_saveobj << (UINT)i << endl;

		// �ش� ������Ʈ�� ������ ������ ����

		pCom->SaveToFile(_saveobj);
	}

	_saveobj << i << endl;

	// ��ũ��Ʈ ���� ����
	const vector<CScript*>& vecScripts = _Obj->GetScripts();
	size_t ScriptCount = vecScripts.size();

	// ��ũ��Ʈ ���� ����
	_saveobj << ScriptCount << endl;


	for (size_t i = 0; i < vecScripts.size(); ++i)
	{
		//SaveWString(CScriptMgr::GetScriptName(vecScripts[i]), _File);
		wstring scriptname;
		scriptname = CScriptMgr::GetScriptName(vecScripts[i]);
		_saveobj << scriptname << endl;
		vecScripts[i]->SaveToFile(_saveobj);
	}

	// �ڽ� ������Ʈ�� ������ �ڽ� ������Ʈ ���� ����
	const vector<CGameObject*>& vecChild = _Obj->GetChild();
	size_t childcount = vecChild.size();

	_saveobj << childcount << endl;

	for (size_t i = 0; i < childcount; ++i)
	{
		SaveGameObject(vecChild[i], _saveobj);
	}
}


CLevel* CLevelSaveLoad::LoadLevel(const wstring& _strLevelPath)
{
	CLevel* pLevel = nullptr;

	// Level �� �ҷ��� ���
	wstring strLevelPath = CPathMgr::GetContentPath();
	strLevelPath += _strLevelPath;

	if (!exists(strLevelPath))
	{
		MessageBox(nullptr, L"���� ��ΰ� �ùٸ��� �ʰų�, ������ ����", L"���� �ε� ����", MB_OK);
		return nullptr;
	}

	ifstream pFile(strLevelPath);

	if(pFile.is_open())
	{
		// ������ �̸��� �д´�.
		pLevel = new CLevel;
		string strLevelName;
		pFile >> strLevelName;
		pLevel->SetName(ToWString(strLevelName));

		// Layer �ε�
		for (UINT i = 0; i < LAYER_MAX; ++i)
		{
			LoadLayer(pLevel->GetLayer(i), pFile);
		}

	}

	



	return pLevel;
}

void CLevelSaveLoad::LoadLayer(CLayer* _Layer, ifstream& _File)
{

	// Layer �� �̸� ����
	string strLayerName;
	_File >> strLayerName;
	_Layer->SetName(strLayerName);


	// Layer �� �����ϴ� GameObject ���� �ҷ��´�.
	size_t ObjCount = 0;
	_File >> ObjCount;

	for (int i = 0; i < ObjCount; ++i)
	{
		CGameObject* pObject = LoadGameObject(_File);
		_Layer->AddObject(pObject, false);
	}

}

CGameObject* CLevelSaveLoad::LoadGameObject(ifstream& _File)
{
	CGameObject* pObject = new CGameObject;
	
	// GameObject �� �̸��� �ε�
	string strName;
	_File >> strName;
	pObject->SetName(strName);

	// obj�� ���̾ ����
	int ObjLayerNum = -1;
	_File >> ObjLayerNum;
	pObject->SetLayerIdx(ObjLayerNum);

	// ������Ʈ ������ �ҷ�����
	COMPONENT_TYPE type = COMPONENT_TYPE::END;
	while(true)
	{
		int num;
		_File >> num;
		type = (COMPONENT_TYPE)num;

		if (COMPONENT_TYPE::END == type)
			break;

		CComponent* pComponent = nullptr;

		switch (type)
		{
		case COMPONENT_TYPE::TRANSFORM:
			pComponent = new CTransform;
			break;
		case COMPONENT_TYPE::COLLIDER2D:
			pComponent = new CCollider2D;
			break;				
		case COMPONENT_TYPE::ANIMATOR2D:
			pComponent = new CAnimator2D;
			break;		
		case COMPONENT_TYPE::LIGHT2D:
			pComponent = new CLight2D;
			break;		
		case COMPONENT_TYPE::CAMERA:
			pComponent = new CCamera;
			break;
		case COMPONENT_TYPE::STATEMACHINE:
			pComponent = new CStateMachine;
			break;
		case COMPONENT_TYPE::MESHRENDER:
			pComponent = new CMeshRender;
			break;
		case COMPONENT_TYPE::TILEMAP:
			pComponent = new CTileMap;
			break;
		case COMPONENT_TYPE::PARTICLESYSTEM:
			pComponent = new CParticleSystem;
			break;
		default:
			assert(nullptr);
			break;
		}


		
		// �ش� ������Ʈ�� ������ �����͸� �ε�
		pObject->AddComponent(pComponent);
		pComponent->LoadFromFile(_File);
	}

	// ��ũ��Ʈ ���� �б�
	size_t ScriptCount = 0;
	_File >> ScriptCount;


	for (size_t i = 0; i < ScriptCount; ++i)
	{
		string strScriptName;
		_File >> strScriptName;

		CScript* pScript = CScriptMgr::GetScript(ToWString(strScriptName));
		pObject->AddComponent(pScript);
		pScript->LoadFromFile(_File);
	}

	// �ڽ� ������Ʈ�� ������ �ڽ� ������Ʈ ���� ����	
	size_t childcount = 0;
	_File >> childcount;

	for (size_t i = 0; i < childcount; ++i)
	{
		pObject->AddChild(LoadGameObject(_File));
	}

	return pObject;
}

#include <Engine/CState.h>
#include <Scripts/CStateMgr.h>

CState* CLevelSaveLoad::LoadState(const string& _strStateNamePath)
{
	return CStateMgr::GetState(ToWString(_strStateNamePath));
}
