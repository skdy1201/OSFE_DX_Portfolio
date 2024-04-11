#include "pch.h"
#include "CStateMgr.h"

#include "CSniperIdleState.h"
#include "CSniperMoveState.h"
#include "CSniperAttackState.h"
#include "CPlayerIdleState.h"
#include "CPlayerEntryState.h"
#include "CPlayerMoveState.h"
#include "CPlayerAttackState.h"
#include "CSniperDeadState.h"
#include "CSniperHitState.h"
#include "CPlayerHitState.h"

void CStateMgr::GetStateInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CSniperIdleState");
	_vec.push_back(L"CSniperMoveState");
	_vec.push_back(L"CSniperAttackState");
	_vec.push_back(L"CPlayerIdleState");
	_vec.push_back(L"CPlayerEntryState");
	_vec.push_back(L"CPlayerMoveState");
	_vec.push_back(L"CPlayerAttackState");
	_vec.push_back(L"CSniperDeadState");
	_vec.push_back(L"CSniperHitState");
	_vec.push_back(L"CPlayerHitState");
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
	if (L"CPlayerAttackState" == _strStateName)
		return new CPlayerAttackState;
	if (L"CSniperDeadState" == _strStateName)
		return new CSniperDeadState;
	if (L"CSniperHitState" == _strStateName)
		return new CSniperHitState;
	if (L"CPlayerHitState" == _strStateName)
		return new CPlayerHitState;
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
	case (UINT)STATE_TYPE::PLAYERATTACKSTATE:
		return new CPlayerAttackState;
		break;
	case (UINT)STATE_TYPE::SNIPERDEADSTATE:
		return new CSniperDeadState;
		break;
	case (UINT)STATE_TYPE::SNIPERHITSTATE:
		return new CSniperHitState;
		break;
	case (UINT)STATE_TYPE::PLAYERHITSTATE:
		return new CPlayerHitState;
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

	case STATE_TYPE::PLAYERATTACKSTATE:
		return L"CPlayerAttackState";
		break;

	case STATE_TYPE::SNIPERDEADSTATE:
		return L"CSniperDeadState";
		break;

	case STATE_TYPE::SNIPERHITSTATE:
		return L"CSniperHitState";
		break;

	case STATE_TYPE::PLAYERHITSTATE:
		return L"CPlayerHitState";
		break;

	}
	return nullptr;
}