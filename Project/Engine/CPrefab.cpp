#include "pch.h"
#include "CPrefab.h"

#include "CGameObject.h"

SAVE_TYPE CPrefab::GAMEOBJECT_SAVE = nullptr;
LOAD_TYPE CPrefab::GAMEOBJECT_LOAD = nullptr;


CPrefab::CPrefab(bool _Engine)
	: CAsset(ASSET_TYPE::PREFAB, _Engine)
	, m_ProtoObj(nullptr)
{
}

CPrefab::CPrefab(CGameObject* _Proto, bool _Engine)
	: CAsset(ASSET_TYPE::PREFAB, _Engine)
	, m_ProtoObj(_Proto)
{
}

CPrefab::~CPrefab()
{
	if (nullptr != m_ProtoObj)
		delete m_ProtoObj;
}

void CPrefab::SetGameObject(CGameObject* _Object)
{
	if (nullptr != m_ProtoObj)
		delete m_ProtoObj;

	m_ProtoObj = _Object;
}

CGameObject* CPrefab::Instantiate()
{
	return m_ProtoObj->Clone();
}

int CPrefab::Save(const wstring& _strRelativePath)
{
	assert(GAMEOBJECT_SAVE);

	wstring strContentPath = CPathMgr::GetContentPath();
	strContentPath += _strRelativePath;

	ofstream pFile;

	pFile.open(strContentPath);
	if(pFile.is_open())
	{
		GAMEOBJECT_SAVE(m_ProtoObj, pFile);
	}
	return S_OK;
}

int CPrefab::Load(const wstring& _strFilePath)
{
	assert(GAMEOBJECT_LOAD);

	ifstream pFile;
	pFile.open(_strFilePath);

	if (!pFile.is_open())
		return E_FAIL;

	m_ProtoObj = GAMEOBJECT_LOAD(pFile);

	return S_OK;
}

CGameObject* CPrefab::GetPrefabObj(wstring NameKey)
{
	CGameObject* Obj;

	Ptr<CPrefab> prefab = CAssetMgr::GetInst()->Load<CPrefab>(NameKey, NameKey);
	Obj = prefab->Instantiate();

	return Obj;
}
