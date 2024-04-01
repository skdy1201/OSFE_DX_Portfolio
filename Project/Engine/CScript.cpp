#include "pch.h"
#include "CScript.h"

CScript::CScript(UINT _ScriptType)
	: CComponent(COMPONENT_TYPE::SCRIPT)
	, m_iScriptType(_ScriptType)
{
}

CScript::CScript(const CScript& _Origin)
	: CComponent(COMPONENT_TYPE::SCRIPT)
	, m_iScriptType(_Origin.m_iScriptType)
{
}

CScript::~CScript()
{
}

tScriptParam CScript::GetScriptParam(string desc)
{
	for(int i = 0; i < m_ScriptParam.size(); ++i)
	{
		if (desc == m_ScriptParam[i].Desc)
		{
			return m_ScriptParam[i];
		}
		else
			continue;
	}
}

void CScript::Instantiate(Ptr<CPrefab> _Prefab, Vec3 _vWorldPos, int _layerIdx)
{
	if (nullptr == _Prefab)
		return;

	CGameObject* pNewObj = _Prefab->Instantiate();

	pNewObj->Transform()->SetRelativePos(_vWorldPos);

	GamePlayStatic::SpawnGameObject(pNewObj, _layerIdx);
}

void CScript::SaveToFile(ofstream& _File)
{

}

void CScript::LoadFromFile(ifstream& _File)
{
}