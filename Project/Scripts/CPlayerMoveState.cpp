#include "pch.h"
#include "CPlayerMoveState.h"

#include  "CFieldObjScript.h"

#include <Engine/CAnimator2D.h>
#include <Engine/CAnim.h>

CPlayerMoveState::CPlayerMoveState()
	: CState((UINT)STATE_TYPE::PLAYERMOVESTATE)
	, Player(nullptr)
	, PlayerScript(nullptr)
	, MoveTimer(nullptr)
{
}

CPlayerMoveState::~CPlayerMoveState()
{
}

void CPlayerMoveState::Enter()
{
}

void CPlayerMoveState::finaltick()
{
}

void CPlayerMoveState::Exit()
{
}
