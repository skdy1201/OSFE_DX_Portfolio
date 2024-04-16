#include "pch.h"
#include "CLurkerDeadState.h"

#include <Engine/CAnim.h>
#include <Engine/CAnimator2D.h>

#include <Engine/CMeshRender.h>
#include <Engine/CMaterial.h>

#include <Engine/CTransform.h>

CLurkerDeadState::CLurkerDeadState()
	: CState((UINT)STATE_TYPE::LURKERDEADSTATE)
{
}

CLurkerDeadState::~CLurkerDeadState()
{
}

void CLurkerDeadState::Enter()
{
	Owner = BlackBoardOwner


	Owner->Transform()->SetOffset(Vec2{ 0.f, 0.f });
	Owner->Transform()->SetRelativeScale(Owner->Transform()->GetRelativeScale() * 1.5);
	Owner->Animator2D()->Play(MonsterDead);
	GamePlayStatic::Play2DSound(L"sound\\explosion_pop.wav", 1, 0.5f);
}

void CLurkerDeadState::finaltick()
{
	if (Owner->Animator2D()->GetCurAnim()->IsFinish())
	{
		GamePlayStatic::DestroyGameObject(Owner);
	}
}

void CLurkerDeadState::Exit()
{
}
