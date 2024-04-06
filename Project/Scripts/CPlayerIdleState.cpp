#include "pch.h"
#include "CPlayerIdleState.h"

#include <Engine/CAnimator2D.h>


CPlayerIdleState::CPlayerIdleState()
	: CState((UINT)STATE_TYPE::PLAYERIDLESTATE)
	, MoveTimer(nullptr)
	, AttackTimer(nullptr)
{
}

CPlayerIdleState::~CPlayerIdleState()
{
}

void CPlayerIdleState::Enter()
{
	Player = (CGameObject*)GetBlackboardData(L"Player");

	Player->Animator2D()->Play(L"SaffronIdle", true);
}

void CPlayerIdleState::finaltick()
{
}

void CPlayerIdleState::Exit()
{
}
