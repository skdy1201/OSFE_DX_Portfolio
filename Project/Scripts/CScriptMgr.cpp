#include "pch.h"
#include "CScriptMgr.h"

#include "CTileScript.h"
#include "CFieldScript.h"
#include "CFieldObjScript.h"
#include "CPlayerCursorScript.h"
#include "CSaffronBullet.h"
#include "CSniperScript.h"
#include "CSniperProj.h"
#include "CProjectileScript.h"
#include "CBackgroundScript.h"
#include "CMissileScript.h"
#include "CMonsterScript.h"
#include "CPlayerScript.h"
#include "CAnimatorModule.h"
#include "CPlayerBulletAnim.h"
#include "CPlayerSpawnAnim.h"
#include "CFrostBolt.h"
#include "CHitAnimationModule.h"
#include "CUIScript.h"
#include "CManaBackGroundUIScript.h"
#include "CManaProgrssUIScript.h"
#include "CManaProgressWhiteUI.h"
#include "CDeckCoverUI.h"
#include "CTerrabeam.h"
#include "CDiagBeam.h"
#include "CPurpleDisc.h"
#include "CChangeRedModule.h"
#include "CTerraScript.h"
#include "CTitleUI.h"
#include "CControlScript.h"
#include "CSpine.h"
#include "CWideShot.h"
#include "CLurkerScript.h"
#include "CLurkerShot.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CTileScript");
	_vec.push_back(L"CFieldScript");
	_vec.push_back(L"CFieldObjScript");
	_vec.push_back(L"CPlayerCursorScript");
	_vec.push_back(L"CSaffronBullet");
	_vec.push_back(L"CSniperScript");
	_vec.push_back(L"CSniperProj");
	_vec.push_back(L"CProjectileScript");
	_vec.push_back(L"CBackgroundScript");
	_vec.push_back(L"CMissileScript");
	_vec.push_back(L"CMonsterScript");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CAnimatorModule");
	_vec.push_back(L"CPlayerBulletAnim");
	_vec.push_back(L"CPlayerSpawnAnim");
	_vec.push_back(L"CFrostBolt");
	_vec.push_back(L"CHitAnimationModule");
	_vec.push_back(L"CUIScript");
	_vec.push_back(L"CManaBackGroundUIScript");
	_vec.push_back(L"CManaProgrssUIScript");
	_vec.push_back(L"CManaProgressWhiteUI");
	_vec.push_back(L"CDeckCoverUI");
	_vec.push_back(L"CTerrabeam");
	_vec.push_back(L"CDiagBeam");
	_vec.push_back(L"CPurpleDisc");
	_vec.push_back(L"CChangeRedModule");
	_vec.push_back(L"CTerraScript");
	_vec.push_back(L"CTitleUI");
	_vec.push_back(L"CControlScript");
	_vec.push_back(L"CSpine");
	_vec.push_back(L"CWideShot");
	_vec.push_back(L"CLurkerScript");
	_vec.push_back(L"CLurkerShot");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CTileScript" == _strScriptName)
		return new CTileScript;
	if (L"CFieldScript" == _strScriptName)
		return new CFieldScript;
	if (L"CFieldObjScript" == _strScriptName)
		return new CFieldObjScript;
	if (L"CPlayerCursorScript" == _strScriptName)
		return new CPlayerCursorScript;
	if (L"CSaffronBullet" == _strScriptName)
		return new CSaffronBullet;
	if (L"CSniperScript" == _strScriptName)
		return new CSniperScript;
	if (L"CSniperProj" == _strScriptName)
		return new CSniperProj;
	if (L"CProjectileScript" == _strScriptName)
		return new CProjectileScript;
	if (L"CBackgroundScript" == _strScriptName)
		return new CBackgroundScript;
	if (L"CMissileScript" == _strScriptName)
		return new CMissileScript;
	if (L"CMonsterScript" == _strScriptName)
		return new CMonsterScript;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CAnimatorModule" == _strScriptName)
		return new CAnimatorModule;
	if (L"CPlayerBulletAnim" == _strScriptName)
		return new CPlayerBulletAnim;
	if (L"CPlayerSpawnAnim" == _strScriptName)
		return new CPlayerSpawnAnim;
	if (L"CFrostBolt" == _strScriptName)
		return new CFrostBolt;
	if (L"CHitAnimationModule" == _strScriptName)
		return new CHitAnimationModule;
	if (L"CUIScript" == _strScriptName)
		return new CUIScript;
	if (L"CManaBackGroundUIScript" == _strScriptName)
		return new CManaBackGroundUIScript;
	if (L"CManaProgrssUIScript" == _strScriptName)
		return new CManaProgrssUIScript;
	if (L"CManaProgressWhiteUI" == _strScriptName)
		return new CManaProgressWhiteUI;
	if (L"CDeckCoverUI" == _strScriptName)
		return new CDeckCoverUI;
	if (L"CTerrabeam" == _strScriptName)
		return new CTerrabeam;
	if (L"CDiagBeam" == _strScriptName)
		return new CDiagBeam;
	if (L"CPurpleDisc" == _strScriptName)
		return new CPurpleDisc;
	if (L"CChangeRedModule" == _strScriptName)
		return new CChangeRedModule;
	if (L"CTerraScript" == _strScriptName)
		return new CTerraScript;
	if (L"CTitleUI" == _strScriptName)
		return new CTitleUI;
	if (L"CControlScript" == _strScriptName)
		return new CControlScript;
	if (L"CSpine" == _strScriptName)
		return new CSpine;
	if (L"CWideShot" == _strScriptName)
		return new CWideShot;
	if (L"CLurkerScript" == _strScriptName)
		return new CLurkerScript;
	if (L"CLurkerShot" == _strScriptName)
		return new CLurkerShot;
	return nullptr;
}

CScript * CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
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
	case (UINT)SCRIPT_TYPE::SAFFRONBULLET:
		return new CSaffronBullet;
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
	case (UINT)SCRIPT_TYPE::BACKGROUNDSCRIPT:
		return new CBackgroundScript;
		break;
	case (UINT)SCRIPT_TYPE::MISSILESCRIPT:
		return new CMissileScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERSCRIPT:
		return new CMonsterScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::ANIMATORMODULE:
		return new CAnimatorModule;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERBULLETANIM:
		return new CPlayerBulletAnim;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSPAWNANIM:
		return new CPlayerSpawnAnim;
		break;
	case (UINT)SCRIPT_TYPE::FROSTBOLT:
		return new CFrostBolt;
		break;
	case (UINT)SCRIPT_TYPE::HITANIMATIONMODULE:
		return new CHitAnimationModule;
		break;
	case (UINT)SCRIPT_TYPE::UISCRIPT:
		return new CUIScript;
		break;
	case (UINT)SCRIPT_TYPE::MANABACKGROUNDUISCRIPT:
		return new CManaBackGroundUIScript;
		break;
	case (UINT)SCRIPT_TYPE::MANAPROGRSSUISCRIPT:
		return new CManaProgrssUIScript;
		break;
	case (UINT)SCRIPT_TYPE::MANAPROGRESSWHITEUI:
		return new CManaProgressWhiteUI;
		break;
	case (UINT)SCRIPT_TYPE::DECKCOVERUI:
		return new CDeckCoverUI;
		break;
	case (UINT)SCRIPT_TYPE::TERRABEAM:
		return new CTerrabeam;
		break;
	case (UINT)SCRIPT_TYPE::DIAGBEAM:
		return new CDiagBeam;
		break;
	case (UINT)SCRIPT_TYPE::PURPLEDISC:
		return new CPurpleDisc;
		break;
	case (UINT)SCRIPT_TYPE::CHANGEREDMODULE:
		return new CChangeRedModule;
		break;
	case (UINT)SCRIPT_TYPE::TERRASCRIPT:
		return new CTerraScript;
		break;
	case (UINT)SCRIPT_TYPE::TITLEUI:
		return new CTitleUI;
		break;
	case (UINT)SCRIPT_TYPE::CONTROLSCRIPT:
		return new CControlScript;
		break;
	case (UINT)SCRIPT_TYPE::SPINE:
		return new CSpine;
		break;
	case (UINT)SCRIPT_TYPE::WIDESHOT:
		return new CWideShot;
		break;
	case (UINT)SCRIPT_TYPE::LURKERSCRIPT:
		return new CLurkerScript;
		break;
	case (UINT)SCRIPT_TYPE::LURKERSHOT:
		return new CLurkerShot;
		break;
	}
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
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

	case SCRIPT_TYPE::SAFFRONBULLET:
		return L"CSaffronBullet";
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

	case SCRIPT_TYPE::BACKGROUNDSCRIPT:
		return L"CBackgroundScript";
		break;

	case SCRIPT_TYPE::MISSILESCRIPT:
		return L"CMissileScript";
		break;

	case SCRIPT_TYPE::MONSTERSCRIPT:
		return L"CMonsterScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
		break;

	case SCRIPT_TYPE::ANIMATORMODULE:
		return L"CAnimatorModule";
		break;

	case SCRIPT_TYPE::PLAYERBULLETANIM:
		return L"CPlayerBulletAnim";
		break;

	case SCRIPT_TYPE::PLAYERSPAWNANIM:
		return L"CPlayerSpawnAnim";
		break;

	case SCRIPT_TYPE::FROSTBOLT:
		return L"CFrostBolt";
		break;

	case SCRIPT_TYPE::HITANIMATIONMODULE:
		return L"CHitAnimationModule";
		break;

	case SCRIPT_TYPE::UISCRIPT:
		return L"CUIScript";
		break;

	case SCRIPT_TYPE::MANABACKGROUNDUISCRIPT:
		return L"CManaBackGroundUIScript";
		break;

	case SCRIPT_TYPE::MANAPROGRSSUISCRIPT:
		return L"CManaProgrssUIScript";
		break;

	case SCRIPT_TYPE::MANAPROGRESSWHITEUI:
		return L"CManaProgressWhiteUI";
		break;

	case SCRIPT_TYPE::DECKCOVERUI:
		return L"CDeckCoverUI";
		break;

	case SCRIPT_TYPE::TERRABEAM:
		return L"CTerrabeam";
		break;

	case SCRIPT_TYPE::DIAGBEAM:
		return L"CDiagBeam";
		break;

	case SCRIPT_TYPE::PURPLEDISC:
		return L"CPurpleDisc";
		break;

	case SCRIPT_TYPE::CHANGEREDMODULE:
		return L"CChangeRedModule";
		break;

	case SCRIPT_TYPE::TERRASCRIPT:
		return L"CTerraScript";
		break;

	case SCRIPT_TYPE::TITLEUI:
		return L"CTitleUI";
		break;

	case SCRIPT_TYPE::CONTROLSCRIPT:
		return L"CControlScript";
		break;

	case SCRIPT_TYPE::SPINE:
		return L"CSpine";
		break;

	case SCRIPT_TYPE::WIDESHOT:
		return L"CWideShot";
		break;

	case SCRIPT_TYPE::LURKERSCRIPT:
		return L"CLurkerScript";
		break;

	case SCRIPT_TYPE::LURKERSHOT:
		return L"CLurkerShot";
		break;

	}
	return nullptr;
}