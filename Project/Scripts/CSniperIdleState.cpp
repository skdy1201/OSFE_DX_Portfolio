#include "pch.h"
#include "CSniperIdleState.h"

CSniperIdleState::CSniperIdleState()
	:CState((UINT)STATE_TYPE::SNIPERIDLESTATE)


{
}

CSniperIdleState::~CSniperIdleState()
{
}

void CSniperIdleState::Enter()
{
	Player = (CGameObject*)GetBlackboardData(L"Player");
	PlayerScript = Player->GetScript<CFieldObjScript>();

	*(float*)GetBlackboardData(L"MoveCooldown") = 0.f;
}

void CSniperIdleState::finaltick()
{
	int PlayerRow = (int)PlayerScript->GetOwnerIdx().y;
	int SniperRow = *(int*)GetBlackboardData(L"Current Row");

	float MoveTimer = *(float*)GetBlackboardData(L"MoveCooldown");
	float AttackTimer = *(float*)GetBlackboardData(L"AttackCooldown");

	if(PlayerRow != SniperRow && MoveTimer >= 2.f)
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
	else if(PlayerRow == SniperRow && AttackTimer >= 5.f)
	{
		ChangeState(L"CSniperAttackState");
	}

}

void CSniperIdleState::Exit()
{
}
