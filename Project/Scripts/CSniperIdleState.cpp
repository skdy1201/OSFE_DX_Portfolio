#include "pch.h"
#include "CSniperIdleState.h"

#include "CSniperScript.h"

CSniperIdleState::CSniperIdleState()
	:CState((UINT)STATE_TYPE::SNIPERIDLESTATE)
	, MoveTimer(nullptr)
	, AttackTimer(nullptr)
{
}

CSniperIdleState::~CSniperIdleState()
{
}

void CSniperIdleState::Enter()
{
	Player = BlackBoardPlayer
	PlayerScript = Player->GetScript<CFieldObjScript>();

	Owner = BlackBoardOwner
	OwnerScript = Owner->GetScript<CSniperScript>();

	MoveTimer = MoveCooldown
	AttackTimer = AttackCooldown

}

void CSniperIdleState::finaltick()
{
	if(OwnerScript->GetStatus().Current_HP <= 0)
	{
		Owner->StateMachine()->GetFSM()->ChangeState(L"CSniperDeadState");
	}

	int PlayerRow = (int)PlayerScript->GetOwnerIdx().y;
	int SniperRow = *(int*)GetBlackboardData(L"Current Row");


	if(PlayerRow != SniperRow && *MoveTimer >= 2.f)
	{
		int* movedir = (int*)GetBlackboardData(L"Move Dir");

		 if(PlayerRow-SniperRow > 0)
		{
			*movedir = 1;
			ChangeState(L"CSniperMoveState");
		}
		else
		{
			*movedir = 2;
			ChangeState(L"CSniperMoveState");

		}
	}
	else if(PlayerRow == SniperRow && *AttackTimer >= 5.f)
	{
		ChangeState(L"CSniperAttackState");
	}

	if(OwnerScript->GetHit() == true)
	{
		ChangeState(L"CSniperHitState");
	}

	if(OwnerScript->GetMovedByAttack() == true)
	{
		ChangeState(L"CSniperMoveState");
	}

}

void CSniperIdleState::Exit()
{

}
