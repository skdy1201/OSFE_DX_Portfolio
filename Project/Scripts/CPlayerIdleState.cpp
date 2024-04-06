#include "pch.h"
#include "CPlayerIdleState.h"

#include "CFieldObjScript.h"

#include <Engine/CAnimator2D.h>
#include <Engine/CAnim.h>


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
	Player = BlackBoardPlayer;
	PlayerScript = Player->GetScript<CFieldObjScript>();

	Player->Animator2D()->Play(L"SaffronIdle", true);
}

void CPlayerIdleState::finaltick()
{
}

void CPlayerIdleState::Exit()
{
}
