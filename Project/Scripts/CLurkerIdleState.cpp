#include "pch.h"
#include "CLurkerIdleState.h"

#include "CLurkerScript.h"

CLurkerIdleState::CLurkerIdleState()
	: CState((UINT)STATE_TYPE::LURKERIDLESTATE)
	, AttackTimer(nullptr)
{
}

CLurkerIdleState::~CLurkerIdleState()
{
}

void CLurkerIdleState::Enter()
{
	Player = BlackBoardPlayer
	PlayerScript = Player->GetScript<CFieldObjScript>();

	Owner = BlackBoardOwner
	OwnerScript = Owner->GetScript<CLurkerScript>();

	AttackTimer = AttackCooldown


	Owner->Animator2D()->Play(L"LurkerIdle", true);
}

void CLurkerIdleState::finaltick()
{
	if (OwnerScript->GetStatus().Current_HP <= 0)
	{
		Owner->StateMachine()->GetFSM()->ChangeState(L"CLurkerDeadState");
	}

	if (OwnerScript->GetHit() == true)
	{
		ChangeState(L"CLurkerHitState");
	}

	if (OwnerScript->GetMovedByAttack() == true)
	{
		ChangeState(L"CLurkerMoveState");
	}

	else if ( *AttackTimer >= 8.5f)
	{
		ChangeState(L"CLurkerAttackState");
	}

}

void CLurkerIdleState::Exit()
{
}
