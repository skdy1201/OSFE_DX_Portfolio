#include "pch.h"
#include "CScriptMgr.h"

#include "CBackgroundScript.h"
#include "CMissileScript.h"
#include "CPlayerScript.h"
#include "CMonsterScript.h"
#include "CTileScript.h"
#include "CFieldScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CBackgroundScript");
	_vec.push_back(L"CMissileScript");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CMonsterScript");
	_vec.push_back(L"CTileScript");
	_vec.push_back(L"CFieldScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CBackgroundScript" == _strScriptName)
		return new CBackgroundScript;
	if (L"CMissileScript" == _strScriptName)
		return new CMissileScript;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CMonsterScript" == _strScriptName)
		return new CMonsterScript;
	if (L"CTileScript" == _strScriptName)
		return new CTileScript;
	if (L"CFieldScript" == _strScriptName)
		return new CFieldScript;
	return nullptr;
}

CScript * CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::BACKGROUNDSCRIPT:
		return new CBackgroundScript;
		break;
	case (UINT)SCRIPT_TYPE::MISSILESCRIPT:
		return new CMissileScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERSCRIPT:
		return new CMonsterScript;
		break;
	case (UINT)SCRIPT_TYPE::TILESCRIPT:
		return new CTileScript;
		break;
	case (UINT)SCRIPT_TYPE::FIELDSCRIPT:
		return new CFieldScript;
		break;
	}
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::BACKGROUNDSCRIPT:
		return L"CBackgroundScript";
		break;

	case SCRIPT_TYPE::MISSILESCRIPT:
		return L"CMissileScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
		break;

	case SCRIPT_TYPE::MONSTERSCRIPT:
		return L"CMonsterScript";
		break;

	case SCRIPT_TYPE::TILESCRIPT:
		return L"CTileScript";
		break;

	case SCRIPT_TYPE::FIELDSCRIPT:
		return L"CFieldScript";
		break;

	}
	return nullptr;
}