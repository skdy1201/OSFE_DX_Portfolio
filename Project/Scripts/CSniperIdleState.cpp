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

}

void CSniperIdleState::finaltick()
{
	int PlayerRow = (int)PlayerScript->GetOwnerIdx().y;
	int SniperRow = *(int*)GetBlackboardData(L"Current Row");

	float MoveTimer = *(float*)GetBlackboardData(L"MoveCooldown");

	if(PlayerRow != SniperRow && MoveTimer == 3.f)
	{
		//ChangeState(L"MoveState");
	}


	//타이머에 따라 플레이어가 자신과 같은 행이 아니라면 이동한다.
	

	
}

void CSniperIdleState::Exit()
{
}
