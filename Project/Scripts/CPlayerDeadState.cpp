#include "pch.h"
#include "CPlayerDeadState.h"

#include <Engine/CAnimator2D.h>
#include <Engine/CAnim.h>

CPlayerDeadState::CPlayerDeadState()
	: CState((UINT)STATE_TYPE::PLAYERDEADSTATE)
{
}

CPlayerDeadState::~CPlayerDeadState()
{
}

void CPlayerDeadState::Enter()
{
	Owner = (CGameObject*)GetBlackboardData(L"Player");

	Owner->Animator2D()->Play(L"SaffronDead", false);

}
void CPlayerDeadState::finaltick()
{
	if (Owner->Animator2D()->GetCurAnim()->IsFinish())
		GamePlayStatic::DestroyGameObject(Owner);

}

void CPlayerDeadState::Exit()
{
}
