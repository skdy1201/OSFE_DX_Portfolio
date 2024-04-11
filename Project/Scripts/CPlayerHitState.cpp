#include "pch.h"
#include "CPlayerHitState.h"

#include <Engine/CAnim.h>

#include "CFieldObjScript.h"

CPlayerHitState::CPlayerHitState()
	: CState((UINT)STATE_TYPE::PLAYERHITSTATE)
	, IsRender(true)
	, Timer(0.2f)
{
}

CPlayerHitState::~CPlayerHitState()
{
}

void CPlayerHitState::Enter()
{
	Player = BlackBoardPlayer;
	PlayerScript = Player->GetScript<CFieldObjScript>();
	Field = PlayerScript->GetField();

	Player->Animator2D()->Play(PlayerHit, false);

	Timer = 0.5f;
}

void CPlayerHitState::finaltick()
{
	if (Player->Animator2D()->GetCurAnim()->IsFinish())
		ChangeState(L"CPlayerIdleState");

	Timer -= DT;

	if(Timer >= 0.f)
	{
		IsRender = IsRender ? true : false;
		Player->MeshRender()->SetRenderPossible(IsRender);
	}
}

void CPlayerHitState::Exit()
{
	PlayerScript->SetHit(false);
}
