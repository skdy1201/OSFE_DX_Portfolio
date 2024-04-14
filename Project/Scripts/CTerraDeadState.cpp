#include "pch.h"
#include "CTerraDeadState.h"

#include <Engine/CTransform.h>
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim.h>

CTerraDeadState::CTerraDeadState()
	: CState((UINT)STATE_TYPE::TERRADEADSTATE)
{
}

CTerraDeadState::~CTerraDeadState()
{
}

void CTerraDeadState::Enter()
{
	Owner = BlackBoardOwner


	Owner->Animator2D()->Play(L"TerraDead");

	animcount = 1;
}

void CTerraDeadState::finaltick()
{
	if (Owner->Animator2D()->GetCurAnim()->IsFinish())
	{
		Owner->Transform()->SetOffset(Vec2{ 0.f, 20.f });
		Owner->Animator2D()->PlayModule(L"DeathExplosion", animcount);
	}

	if (Owner->Animator2D()->GetCurAnim()->GetName() == L"DeathExplosion" && Owner->Animator2D()->GetCurAnim()->IsFinish())
	{
		GamePlayStatic::DestroyGameObject(Owner);
	}
}


void CTerraDeadState::Exit()
{
}
