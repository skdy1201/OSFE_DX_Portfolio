#include "pch.h"
#include "CStateMgr.h"

#include "CSniperIdleState.h"
#include "CSniperMoveState.h"
#include "CSniperAttackState.h"
#include "CPlayerIdleState.h"
#include "CPlayerEntryState.h"
#include "CPlayerMoveState.h"

void CStateMgr::GetStateInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CSniperIdleState");
	_vec.push_back(L"CSniperMoveState");
	_vec.push_back(L"CSniperAttackState");
	_vec.push_back(L"CPlayerIdleState");
	_vec.push_back(L"CPlayerEntryState");
	_vec.push_back(L"CPlayerMoveState");
}

CState * CStateMgr::GetState(const wstring& _strStateName)
{
	if (L"CSniperIdleState" == _strStateName)
		return new CSniperIdleState;
	if (L"CSniperMoveState" == _strStateName)
		return new CSniperMoveState;
	if (L"CSniperAttackState" == _strStateName)
		return new CSniperAttackState;
	if (L"CPlayerIdleState" == _strStateName)
		return new CPlayerIdleState;
	if (L"CPlayerEntryState" == _strStateName)
		return new CPlayerEntryState;
	if (L"CPlayerMoveState" == _strStateName)
		return new CPlayerMoveState;
	return nullptr;
}

CState * CStateMgr::GetState(UINT _iStateType)
{
	switch (_iStateType)
	{
	case (UINT)STATE_TYPE::SNIPERIDLESTATE:
		return new CSniperIdleState;
		break;
	case (UINT)STATE_TYPE::SNIPERMOVESTATE:
		return new CSniperMoveState;
		break;
	case (UINT)STATE_TYPE::SNIPERATTACKSTATE:
		return new CSniperAttackState;
		break;
	case (UINT)STATE_TYPE::PLAYERIDLESTATE:
		return new CPlayerIdleState;
		break;
	case (UINT)STATE_TYPE::PLAYERENTRYSTATE:
		return new CPlayerEntryState;
		break;
	case (UINT)STATE_TYPE::PLAYERMOVESTATE:
		return new CPlayerMoveState;
		break;
	}
	return nullptr;
}

const wchar_t * CStateMgr::GetStateName(CState * _pState)
{
	switch ((STATE_TYPE)_pState->GetStateType())
	{
	case STATE_TYPE::SNIPERIDLESTATE:
		return L"CSniperIdleState";
		break;

	case STATE_TYPE::SNIPERMOVESTATE:
		return L"CSniperMoveState";
		break;

	case STATE_TYPE::SNIPERATTACKSTATE:
		return L"CSniperAttackState";
		break;

	case STATE_TYPE::PLAYERIDLESTATE:
		return L"CPlayerIdleState";
		break;

	case STATE_TYPE::PLAYERENTRYSTATE:
		return L"CPlayerEntryState";
		break;

	case STATE_TYPE::PLAYERMOVESTATE:
		return L"CPlayerMoveState";
		break;

	}
	return nullptr;
}