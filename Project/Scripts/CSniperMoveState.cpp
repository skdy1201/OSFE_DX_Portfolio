#include "pch.h"
#include "CSniperMoveState.h"

#include "CFieldObjScript.h"
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
	SniperScript = pOwner->GetScript<CFieldObjScript>();

	MoveDir = (int*)GetBlackboardData(L"Move Dir");

	m_OwnerIdx = SniperScript->GetOwnerIdx();
}

void CSniperMoveState::finaltick()
{
	if(*MoveDir == 1)
	{
		SniperScript->GetField()->MoveToTile(SniperScript->GetOwner(), Vec2(m_OwnerIdx.x, m_OwnerIdx.y + 1), PlayerZ);
	}
	else
	{
		SniperScript->GetField()->MoveToTile(SniperScript->GetOwner(), Vec2(m_OwnerIdx.x, m_OwnerIdx.y - 1), PlayerZ);

	}

	*MoveDir = 0;
	float* Timer = (float*)GetBlackboardData(L"MoveCooldown");
	*Timer = 0.f;

	ChangeState(L"CSniperIdleState");
}

void CSniperMoveState::Exit()
{
}
