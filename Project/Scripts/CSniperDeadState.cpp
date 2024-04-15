#include "pch.h"
#include "CSniperDeadState.h"

#include <Engine/CAnim.h>
#include <Engine/CAnimator2D.h>

#include <Engine/CMeshRender.h>
#include <Engine/CMaterial.h>

#include <Engine/CTransform.h>

CSniperDeadState::CSniperDeadState()
	: CState((UINT)STATE_TYPE::SNIPERDEADSTATE)
{
}

CSniperDeadState::~CSniperDeadState()
{
}

void CSniperDeadState::Enter()
{
	Owner = BlackBoardOwner

	Ptr<CMaterial>pMtrl = Owner->MeshRender()->GetMaterial();
	pMtrl->SetScalarParam(SCALAR_PARAM::INT_0, 2);
	pMtrl->SetScalarParam(SCALAR_PARAM::INT_1, 1);

	Owner->Transform()->SetOffset(Vec2{ 0.f, 50.f });
	Owner->Transform()->SetRelativeScale(Owner->Transform()->GetRelativeScale() * 2);
	Owner->Animator2D()->Play(MonsterDead);
	GamePlayStatic::Play2DSound(L"sound\\explosion_pop.wav", 1, 0.5f);

}

void CSniperDeadState::finaltick()
{
	if(Owner->Animator2D()->GetCurAnim()->IsFinish())
	{
		GamePlayStatic::DestroyGameObject(Owner);
	}
}

void CSniperDeadState::Exit()
{
}
