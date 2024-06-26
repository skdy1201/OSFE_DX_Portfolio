#include "pch.h"
#include "CTerraIdleState.h"

#include <Engine/CStateMachine.h>

#include "CTerraScript.h"

CTerraIdleState::CTerraIdleState()
	: CState((UINT)STATE_TYPE::TERRAIDLESTATE)
{
}

CTerraIdleState::~CTerraIdleState()
{
}

void CTerraIdleState::Enter()
{
	TerraScript = this->GetFSM()->GetStateMachine()->GetOwner()->GetScript<CTerraScript>();

	this->GetFSM()->GetStateMachine()->GetOwner()->Animator2D()->Play(TerraIdle);

	MoveCooldtime = MoveCooldown
	AttackCooltime = AttackCooldown
}

void CTerraIdleState::finaltick()
{
	if (TerraScript->GetStatus().Current_HP <= 0)
	{
		ChangeState(L"CTerraDeadState");
	}

	if(*MoveCooldtime >= 10.f)
	{
		ChangeState(L"CTerraMoveState");
	}

	if (*AttackCooltime >= 5.f)
	{
		ChangeState(L"CTerraAttackState");
	}

	if (TerraScript->GetHit() == true)
	{
		ChangeState(L"CTerraHitState");
	}

	if (TerraScript->GetMovedByAttack() == true)
	{
		ChangeState(L"CTerraMoveState");
	}
}

void CTerraIdleState::Exit()
{
}
