#include "pch.h"
#include "CScriptMgr.h"

#include "CBackgroundScript.h"
#include "CMissileScript.h"
#include "CPlayerScript.h"
#include "CMonsterScript.h"
#include "CTileScript.h"
#include "CFieldScript.h"
#include "CFieldObjScript.h"
#include "CPlayerCursorScript.h"
#include "CShaffronBullet.h"
#include "CFrostBolt.h"
#include "CSniperScript.h"
#include "CSniperProj.h"
#include "CProjectileScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CBackgroundScript");
	_vec.push_back(L"CMissileScript");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CMonsterScript");
	_vec.push_back(L"CTileScript");
	_vec.push_back(L"CFieldScript");
	_vec.push_back(L"CFieldObjScript");
	_vec.push_back(L"CPlayerCursorScript");
	_vec.push_back(L"CShaffronBullet");
	_vec.push_back(L"CFrostBolt");
	_vec.push_back(L"CSniperScript");
	_vec.push_back(L"CSniperProj");
	_vec.push_back(L"CProjectileScript");
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
	if (L"CFieldObjScript" == _strScriptName)
		return new CFieldObjScript;
	if (L"CPlayerCursorScript" == _strScriptName)
		return new CPlayerCursorScript;
	if (L"CShaffronBullet" == _strScriptName)
		return new CShaffronBullet;
	if (L"CFrostBolt" == _strScriptName)
		return new CFrostBolt;
	if (L"CSniperScript" == _strScriptName)
		return new CSniperScript;
	if (L"CSniperProj" == _strScriptName)
		return new CSniperProj;
	if (L"CProjectileScript" == _strScriptName)
		return new CProjectileScript;
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
	case (UINT)SCRIPT_TYPE::FIELDOBJSCRIPT:
		return new CFieldObjScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERCURSORSCRIPT:
		return new CPlayerCursorScript;
		break;
	case (UINT)SCRIPT_TYPE::SHAFFRONBULLET:
		return new CShaffronBullet;
		break;
	case (UINT)SCRIPT_TYPE::FROSTBOLT:
		return new CFrostBolt;
		break;
	case (UINT)SCRIPT_TYPE::SNIPERSCRIPT:
		return new CSniperScript;
		break;
	case (UINT)SCRIPT_TYPE::SNIPERPROJ:
		return new CSniperProj;
		break;
	case (UINT)SCRIPT_TYPE::PROJECTILESCRIPT:
		return new CProjectileScript;
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

	case SCRIPT_TYPE::FIELDOBJSCRIPT:
		return L"CFieldObjScript";
		break;

	case SCRIPT_TYPE::PLAYERCURSORSCRIPT:
		return L"CPlayerCursorScript";
		break;

	case SCRIPT_TYPE::SHAFFRONBULLET:
		return L"CShaffronBullet";
		break;

	case SCRIPT_TYPE::FROSTBOLT:
		return L"CFrostBolt";
		break;

	case SCRIPT_TYPE::SNIPERSCRIPT:
		return L"CSniperScript";
		break;

	case SCRIPT_TYPE::SNIPERPROJ:
		return L"CSniperProj";
		break;

	case SCRIPT_TYPE::PROJECTILESCRIPT:
		return L"CProjectileScript";
		break;

	}
	return nullptr;
}