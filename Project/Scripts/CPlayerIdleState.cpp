#include "pch.h"
#include "CPlayerIdleState.h"

#include "CFieldScript.h"
#include "CFieldObjScript.h"
#include "CProjectileScript.h"

#include <Engine/CAnimator2D.h>
#include <Engine/CAnim.h>



CPlayerIdleState::CPlayerIdleState()
	: CState((UINT)STATE_TYPE::PLAYERIDLESTATE)
	, AttackTimer(0.f)
	, AttackRelayTimer(0.f)
{
}

CPlayerIdleState::~CPlayerIdleState()
{
}

void CPlayerIdleState::Enter()
{
	Player = BlackBoardPlayer;
	PlayerScript = Player->GetScript<CFieldObjScript>();
	Field = PlayerScript->GetField();

	Player->Animator2D()->Play(PlayerIdle, true);

}



void CPlayerIdleState::finaltick()
{
	if (KEY_TAP(KEY::UP))
	{
		*(Vec2*)GetBlackboardData(L"NextIdx") = Vec2(0, 1);
		Player->Animator2D()->Play(L"SaffronMoveUp", false);


		Player->StateMachine()->GetFSM()->ChangeState(L"CPlayerMoveState");
	}

	if (KEY_TAP(KEY::DOWN))
	{
		*(Vec2*)GetBlackboardData(L"NextIdx") = Vec2(0, -1);
		Player->Animator2D()->Play(L"SaffronMoveDown", false);


		Player->StateMachine()->GetFSM()->ChangeState(L"CPlayerMoveState");
	}

	if (KEY_TAP(KEY::LEFT))
	{
		*(Vec2*)GetBlackboardData(L"NextIdx") = Vec2(-1, 0);
		Player->Animator2D()->Play(L"SaffronMoveBack", false);

		Player->StateMachine()->GetFSM()->ChangeState(L"CPlayerMoveState");
	}

	if (KEY_TAP(KEY::RIGHT))
	{
		*(Vec2*)GetBlackboardData(L"NextIdx") = Vec2(1, 0);
		Player->Animator2D()->Play(L"SaffronMoveFront", false);

		Player->StateMachine()->GetFSM()->ChangeState(L"CPlayerMoveState");
	}

	if (KEY_PRESSED(KEY::E))
	{
		Player->StateMachine()->GetFSM()->ChangeState(L"CPlayerAttackState");
	}

}

void CPlayerIdleState::Exit()
{


}


