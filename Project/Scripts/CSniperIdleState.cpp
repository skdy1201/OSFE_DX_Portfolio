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

}

void CSniperIdleState::finaltick()
{
	int PlayerRow = (int)PlayerScript->GetOwnerIdx().y;
	int SniperRow = *(int*)GetBlackboardData(L"Current Row");

	float MoveTimer = *(float*)GetBlackboardData(L"MoveCooldown");

	if(PlayerRow != SniperRow && MoveTimer >= 3.f)
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


	//타이머에 따라 플레이어가 자신과 같은 행이 아니라면 이동한다.
	

	
}

void CSniperIdleState::Exit()
{
}
