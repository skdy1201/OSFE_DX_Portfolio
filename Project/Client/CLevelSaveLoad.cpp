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

	// Level 을 저장할 경로
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
	// Layer 의 이름 저장
	if(_Layer->GetName() == "")
	{
		string num;
		_savelayer << to_string (_Layer->GetLayerIdx()) << endl;

	}
	else
	_savelayer << _Layer->GetName() << endl;


	// Layer 가 보유하고 있는 GameObject 들을 저장
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
	// GameObject 의 이름을 저장
	_saveobj << _Obj->GetName() << endl;

	// obj의 레이어를 저장
	int ObjLayerNum = 0;
	ObjLayerNum = _Obj->GetLayerIdx();

	_saveobj << ObjLayerNum << endl;

	// 컴포넌트 정보를 저장
	UINT i = 0;
	for ( ; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		CComponent* pCom = _Obj->GetComponent((COMPONENT_TYPE)i);
		if (nullptr == pCom)
			continue;

		// 컴포넌트 타입 정보 저장

		_saveobj << (UINT)i << endl;

		// 해당 컴포넌트가 저장할 데이터 저장

		pCom->SaveToFile(_saveobj);
	}

	_saveobj << i << endl;

	// 스크립트 정보 저장
	const vector<CScript*>& vecScripts = _Obj->GetScripts();
	size_t ScriptCount = vecScripts.size();

	// 스크립트 개수 저장
	_saveobj << ScriptCount << endl;


	for (size_t i = 0; i < vecScripts.size(); ++i)
	{
		//SaveWString(CScriptMgr::GetScriptName(vecScripts[i]), _File);
		wstring scriptname;
		scriptname = CScriptMgr::GetScriptName(vecScripts[i]);
		_saveobj << scriptname << endl;
		vecScripts[i]->SaveToFile(_saveobj);
	}

	// 자식 오브젝트가 있으면 자식 오브젝트 정보 저장
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

	// Level 을 불러올 경로
	wstring strLevelPath = CPathMgr::GetContentPath();
	strLevelPath += _strLevelPath;

	if (!exists(strLevelPath))
	{
		MessageBox(nullptr, L"레벨 경로가 올바르지 않거나, 레벨이 없음", L"레벨 로드 실패", MB_OK);
		return nullptr;
	}

	ifstream pFile(strLevelPath);

	if(pFile.is_open())
	{
		// 레벨의 이름을 읽는다.
		pLevel = new CLevel;
		string strLevelName;
		pFile >> strLevelName;
		pLevel->SetName(ToWString(strLevelName));

		// Layer 로드
		for (UINT i = 0; i < LAYER_MAX; ++i)
		{
			LoadLayer(pLevel->GetLayer(i), pFile);
		}

	}

	



	return pLevel;
}

void CLevelSaveLoad::LoadLayer(CLayer* _Layer, ifstream& _File)
{

	// Layer 의 이름 저장
	string strLayerName;
	_File >> strLayerName;
	_Layer->SetName(strLayerName);


	// Layer 가 보유하던 GameObject 들을 불러온다.
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
	
	// GameObject 의 이름을 로드
	string strName;
	_File >> strName;
	pObject->SetName(strName);

	// obj의 레이어를 저장
	int ObjLayerNum = -1;
	_File >> ObjLayerNum;
	pObject->SetLayerIdx(ObjLayerNum);

	// 컴포넌트 정보를 불러오기
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


		
		// 해당 컴포넌트가 저장한 데이터를 로드
		pObject->AddComponent(pComponent);
		pComponent->LoadFromFile(_File);
	}

	// 스크립트 개수 읽기
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

	// 자식 오브젝트가 있으면 자식 오브젝트 정보 저장	
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
