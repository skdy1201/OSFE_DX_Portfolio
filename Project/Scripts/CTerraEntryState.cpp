#include "pch.h"
#include "CTerraEntryState.h"

#include <Engine/CStateMachine.h>

#include <Engine/CAnimator2D.h>
#include <Engine/CAnim.h>

#include <Engine/CTransform.h>

#include  <Engine/CGameObject.h>
#include "CFieldObjScript.h"

CTerraEntryState::CTerraEntryState()
	: CState((UINT)STATE_TYPE::TERRAENTRYSTATE)
{
}

CTerraEntryState::~CTerraEntryState()
{
}

void CTerraEntryState::Enter()
{
	Terra = this->GetFSM()->GetStateMachine()->GetOwner();
	TerraFieldScript = Terra->GetScript<CFieldObjScript>();

	Terra->Animator2D()->Play(TerraSpawn, false);
}

void CTerraEntryState::finaltick()
{
	if(Terra->Animator2D()->GetCurAnim()->IsFinish())
	{
		ChangeState(TerraIdleState);
	}

}

void CTerraEntryState::Exit()
{
}
