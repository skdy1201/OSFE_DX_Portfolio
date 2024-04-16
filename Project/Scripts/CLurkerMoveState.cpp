#include "pch.h"
#include "CLurkerMoveState.h"

#include "CLurkerScript.h"

CLurkerMoveState::CLurkerMoveState()
	: CState((UINT)STATE_TYPE::LURKERMOVESTATE)
{
}

CLurkerMoveState::~CLurkerMoveState()
{
}

void CLurkerMoveState::Enter()
{
	Lurker = (CGameObject*)GetBlackboardData(L"Owner");
	OwnerScript = Lurker->GetScript<CLurkerScript>();

	m_OwnerIdx = OwnerScript->GetOwnerIdx();

	Attackcooltime = (float*)GetBlackboardData(L"AttackCooldown");
}

void CLurkerMoveState::finaltick()
{
	OwnerScript->MovedByAttack();

	if (OwnerScript->GetOwnerIdx() == Vec2(OwnerScript->GetOwnerIdx().x + OwnerScript->GetMovedIdx().x, OwnerScript->GetOwnerIdx().y + OwnerScript->GetMovedIdx().y))
	{
		if(*Attackcooltime >= 8.5f)
		{
			ChangeState(L"CLurkerAttackState");
		}
		else
		{
			ChangeState(L"CLurkerIdleState");

		}
	}
}

void CLurkerMoveState::Exit()
{

	if(*Attackcooltime >= 6.f)
	{
		*Attackcooltime -= 3.f;
	}

}
