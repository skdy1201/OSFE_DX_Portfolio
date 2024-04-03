#include "pch.h"
#include "CSniperAttackState.h"

#include <Engine/CAnimator2D.h>
#include <Engine/CAnim.h>

CSniperAttackState::CSniperAttackState()
	: CState((UINT)STATE_TYPE::SNIPERATTACKSTATE)
{
}

CSniperAttackState::~CSniperAttackState()
{
}

void CSniperAttackState::Enter()
{
	Sniper = (CGameObject*)GetBlackboardData(L"Owner");

	

	//AnimatorObject

	//SniperShoot

	Sniper->Animator2D()->Play(L"SniperShoot", false);

}

void CSniperAttackState::finaltick()
{
	if(Sniper->Animator2D()->GetCurAnim()->IsFinish())
	{
		ChangeState(L"CSniperIdleState");
	}
}

void CSniperAttackState::Exit()
{
}
