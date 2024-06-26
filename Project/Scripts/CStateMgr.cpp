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
#include "CTerraEntryState.h"
#include "CTerraMoveState.h"
#include "CTerraIdleState.h"
#include "CTerraHitState.h"
#include "CTerraDeadState.h"
#include "CTerraAttackState.h"
#include "CPlayerDeadState.h"
#include "CLurkerIdleState.h"
#include "CLurkerMoveState.h"
#include "CLurkerHitState.h"
#include "CLurkerDeadState.h"
#include "CLurkerAttackState.h"

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
	_vec.push_back(L"CTerraEntryState");
	_vec.push_back(L"CTerraMoveState");
	_vec.push_back(L"CTerraIdleState");
	_vec.push_back(L"CTerraHitState");
	_vec.push_back(L"CTerraDeadState");
	_vec.push_back(L"CTerraAttackState");
	_vec.push_back(L"CPlayerDeadState");
	_vec.push_back(L"CLurkerIdleState");
	_vec.push_back(L"CLurkerMoveState");
	_vec.push_back(L"CLurkerHitState");
	_vec.push_back(L"CLurkerDeadState");
	_vec.push_back(L"CLurkerAttackState");
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
	if (L"CTerraEntryState" == _strStateName)
		return new CTerraEntryState;
	if (L"CTerraMoveState" == _strStateName)
		return new CTerraMoveState;
	if (L"CTerraIdleState" == _strStateName)
		return new CTerraIdleState;
	if (L"CTerraHitState" == _strStateName)
		return new CTerraHitState;
	if (L"CTerraDeadState" == _strStateName)
		return new CTerraDeadState;
	if (L"CTerraAttackState" == _strStateName)
		return new CTerraAttackState;
	if (L"CPlayerDeadState" == _strStateName)
		return new CPlayerDeadState;
	if (L"CLurkerIdleState" == _strStateName)
		return new CLurkerIdleState;
	if (L"CLurkerMoveState" == _strStateName)
		return new CLurkerMoveState;
	if (L"CLurkerHitState" == _strStateName)
		return new CLurkerHitState;
	if (L"CLurkerDeadState" == _strStateName)
		return new CLurkerDeadState;
	if (L"CLurkerAttackState" == _strStateName)
		return new CLurkerAttackState;
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
	case (UINT)STATE_TYPE::TERRAENTRYSTATE:
		return new CTerraEntryState;
		break;
	case (UINT)STATE_TYPE::TERRAMOVESTATE:
		return new CTerraMoveState;
		break;
	case (UINT)STATE_TYPE::TERRAIDLESTATE:
		return new CTerraIdleState;
		break;
	case (UINT)STATE_TYPE::TERRAHITSTATE:
		return new CTerraHitState;
		break;
	case (UINT)STATE_TYPE::TERRADEADSTATE:
		return new CTerraDeadState;
		break;
	case (UINT)STATE_TYPE::TERRAATTACKSTATE:
		return new CTerraAttackState;
		break;
	case (UINT)STATE_TYPE::PLAYERDEADSTATE:
		return new CPlayerDeadState;
		break;
	case (UINT)STATE_TYPE::LURKERIDLESTATE:
		return new CLurkerIdleState;
		break;
	case (UINT)STATE_TYPE::LURKERMOVESTATE:
		return new CLurkerMoveState;
		break;
	case (UINT)STATE_TYPE::LURKERHITSTATE:
		return new CLurkerHitState;
		break;
	case (UINT)STATE_TYPE::LURKERDEADSTATE:
		return new CLurkerDeadState;
		break;
	case (UINT)STATE_TYPE::LURKERATTACKSTATE:
		return new CLurkerAttackState;
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

	case STATE_TYPE::TERRAENTRYSTATE:
		return L"CTerraEntryState";
		break;

	case STATE_TYPE::TERRAMOVESTATE:
		return L"CTerraMoveState";
		break;

	case STATE_TYPE::TERRAIDLESTATE:
		return L"CTerraIdleState";
		break;

	case STATE_TYPE::TERRAHITSTATE:
		return L"CTerraHitState";
		break;

	case STATE_TYPE::TERRADEADSTATE:
		return L"CTerraDeadState";
		break;

	case STATE_TYPE::TERRAATTACKSTATE:
		return L"CTerraAttackState";
		break;

	case STATE_TYPE::PLAYERDEADSTATE:
		return L"CPlayerDeadState";
		break;

	case STATE_TYPE::LURKERIDLESTATE:
		return L"CLurkerIdleState";
		break;

	case STATE_TYPE::LURKERMOVESTATE:
		return L"CLurkerMoveState";
		break;

	case STATE_TYPE::LURKERHITSTATE:
		return L"CLurkerHitState";
		break;

	case STATE_TYPE::LURKERDEADSTATE:
		return L"CLurkerDeadState";
		break;

	case STATE_TYPE::LURKERATTACKSTATE:
		return L"CLurkerAttackState";
		break;

	}
	return nullptr;
}