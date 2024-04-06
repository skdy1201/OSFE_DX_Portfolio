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
	MoveCooldown = (float*)GetBlackboardData(L"MoveCooldown");


	m_OwnerIdx = SniperScript->GetOwnerIdx();

}

void CSniperMoveState::finaltick()
{
	Vec3 SniperPos = {};

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

	*MoveCooldown = 0.f;
	ChangeState(L"CSniperIdleState");
}

void CSniperMoveState::Exit()
{
	
}
