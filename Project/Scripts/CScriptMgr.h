#pragma once

#include <vector>
#include <string>

enum class SCRIPT_TYPE
{
	TILESCRIPT,
	FIELDSCRIPT,
	FIELDOBJSCRIPT,
	PLAYERCURSORSCRIPT,
	SAFFRONBULLET,
	SNIPERSCRIPT,
	SNIPERPROJ,
	PROJECTILESCRIPT,
	BACKGROUNDSCRIPT,
	MISSILESCRIPT,
	MONSTERSCRIPT,
	PLAYERSCRIPT,
	ANIMATORMODULE,
	PLAYERBULLETANIM,
	PLAYERSPAWNANIM,
	FROSTBOLT,
	HITANIMATIONMODULE,
	UISCRIPT,
	MANABACKGROUNDUISCRIPT,
	MANAPROGRSSUISCRIPT,
	MANAPROGRESSWHITEUI,
	DECKCOVERUI,
	TERRABEAM,
	DIAGBEAM,
	PURPLEDISC,
	CHANGEREDMODULE,
	END,
};

using namespace std;

class CScript;

class CScriptMgr
{
public:
	static void GetScriptInfo(vector<wstring>& _vec);
	static CScript * GetScript(const wstring& _strScriptName);
	static CScript * GetScript(UINT _iScriptType);
	static const wchar_t * GetScriptName(CScript * _pScript);
};
