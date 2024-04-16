#include "pch.h"
#include "CSniperMoveState.h"

#include "CSniperScript.h"
#include "CFieldScript.h"

CSniperMoveState::CSniperMoveState()
	: CState((UINT)STATE_TYPE::SNIPERMOVESTATE)
{
}

CSniperMoveState::~CSniperMoveState()
{
}

void CSniperMoveState::Enter()
{
	CGameObject* pOwner = (CGameObject*)GetBlackboardData(L"Owner");
	SniperScript = pOwner->GetScript<CSniperScript>();

	MoveDir = (int*)GetBlackboardData(L"Move Dir");
	MoveCooldtime = (float*)GetBlackboardData(L"MoveCooldown");

	AttackCooltime = (float*)GetBlackboardData(L"AttackCooldown");

	m_OwnerIdx = SniperScript->GetOwnerIdx();

}

void CSniperMoveState::finaltick()
{
	Vec3 SniperPos = {};

	if(SniperScript->GetMovedByAttack())
	{
		SniperScript->MovedByAttack();

		if(SniperScript->GetOwnerIdx() == Vec2(SniperScript->GetOwnerIdx().x + SniperScript->GetMovedIdx().x, SniperScript->GetOwnerIdx().y + SniperScript->GetMovedIdx().y))
		{

			*MoveCooldtime = 0.f;

			ChangeState(L"CSniperIdleState");

		}
	}
	else
	{

		if(*MoveDir == 1)
		{
			SniperPos = SniperScript->GetField()->GetNextTilePos(SniperScript->GetOwner(), Vec2(m_OwnerIdx.x, m_OwnerIdx.y + 1), PlayerZ);
		}
		else
		{
			SniperPos = SniperScript->GetField()->GetNextTilePos(SniperScript->GetOwner(), Vec2(m_OwnerIdx.x, m_OwnerIdx.y - 1), PlayerZ);
		}

		SniperScript->GetOwner()->Transform()->SetRelativePos(SniperPos);

		*MoveDir = 0;

		*MoveCooldtime = 0.f;

		ChangeState(L"CSniperIdleState");

	}
}

void CSniperMoveState::Exit()
{
	if (*AttackCooltime > 3.5f)
		*AttackCooltime -= 1.0f;
}
