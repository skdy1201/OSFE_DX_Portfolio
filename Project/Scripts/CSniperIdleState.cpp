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


	//Ÿ�̸ӿ� ���� �÷��̾ �ڽŰ� ���� ���� �ƴ϶�� �̵��Ѵ�.
	

	
}

void CSniperIdleState::Exit()
{
}
