#include "pch.h"
#include "CSniperIdleState.h"

#include "CFieldObjScript.h"

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
	Player = (CGameObject*)GetBlackboardData(L"Player");
	PlayerScript = Player->GetScript<CFieldObjScript>();

	MoveTimer = (float*)GetBlackboardData(L"MoveCooldown");
	AttackTimer = (float*)GetBlackboardData(L"AttackCooldown");

	if (*MoveTimer > 3.5f)
		*MoveTimer -= 1.5f;

	if (*AttackTimer > 3.5f)
		*AttackTimer -= 1.0f;


}

void CSniperIdleState::finaltick()
{
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

}

void CSniperIdleState::Exit()
{
}
