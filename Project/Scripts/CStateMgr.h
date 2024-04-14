#pragma once

#include <vector>
#include <string>

enum class STATE_TYPE
{
	SNIPERIDLESTATE,
	SNIPERMOVESTATE,
	SNIPERATTACKSTATE,
	PLAYERIDLESTATE,
	PLAYERENTRYSTATE,
	PLAYERMOVESTATE,
	PLAYERATTACKSTATE,
	SNIPERDEADSTATE,
	SNIPERHITSTATE,
	PLAYERHITSTATE,
	TERRAENTRYSTATE,
	TERRAMOVESTATE,
	TERRAIDLESTATE,
	TERRAHITSTATE,
	TERRADEADSTATE,
	TERRAATTACKSTATE,
	END,
};

using namespace std;

class CState;

class CStateMgr
{
public: 
	static void GetStateInfo(vector<wstring>& _vec);
	static CState* GetState(const wstring& _strStateName);
	static CState* GetState(UINT _iStateType);
	static const wchar_t* GetStateName(CState* _pState);
};
