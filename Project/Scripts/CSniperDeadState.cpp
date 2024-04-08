#include "pch.h"
#include "CSniperDeadState.h"

#include <Engine/CAnim.h>
#include <Engine/CAnimator2D.h>

#include <Engine/CMeshRender.h>
#include <Engine/CMaterial.h>

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
	pMtrl->SetScalarParam(SCALAR_PARAM::INT_0, 0);
	pMtrl->SetScalarParam(SCALAR_PARAM::INT_1, 1);

	Owner->Animator2D()->Play(MonsterDead);
}

void CSniperDeadState::finaltick()
{
	if(Owner->Animator2D()->GetCurAnim()->IsFinish())
	{
		Owner->Destroy();
	}
}

void CSniperDeadState::Exit()
{
}
