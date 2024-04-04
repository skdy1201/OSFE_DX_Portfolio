#include "pch.h"
#include "CSniperAttackState.h"

#include <Engine/CAnimator2D.h>
#include <Engine/CAnim.h>

#include <Engine/CMeshRender.h>
#include <Engine/CMaterial.h>


CSniperAttackState::CSniperAttackState()
	: CState((UINT)STATE_TYPE::SNIPERATTACKSTATE)
{
}

CSniperAttackState::~CSniperAttackState()
{
}

void CSniperAttackState::Enter()
{
	Sniper = (CGameObject*)GetBlackboardData(L"Owner");
	AnimatorObject = (CGameObject*)GetBlackboardData(L"ChildAnim");


	//SniperShoot

	Ptr<CMaterial> pMtrl = AnimatorObject->MeshRender()->GetMaterial();
	pMtrl->SetScalarParam(SCALAR_PARAM::INT_0, 1);

	pMtrl = Sniper->MeshRender()->GetMaterial();
	pMtrl->SetScalarParam(SCALAR_PARAM::INT_0, 0);
	pMtrl->SetScalarParam(SCALAR_PARAM::INT_1, 1);
	Sniper->Animator2D()->Play(L"SniperShoot", false);
	AnimatorObject->Animator2D()->Play(L"ChargeCircle", false);
}

void CSniperAttackState::finaltick()
{
	if(Sniper->Animator2D()->GetCurAnim()->IsFinish())
	{
		ChangeState(L"CSniperIdleState");
	}
}

void CSniperAttackState::Exit()
{
	Ptr<CMaterial> pMtrl = AnimatorObject->MeshRender()->GetMaterial();
	pMtrl->SetScalarParam(SCALAR_PARAM::INT_0, 0);

	pMtrl = Sniper->MeshRender()->GetMaterial();
	pMtrl->SetScalarParam(SCALAR_PARAM::INT_0, 1);
	pMtrl->SetScalarParam(SCALAR_PARAM::INT_1, 0);

	AnimatorObject->Animator2D()->Play(L"EmptyAnimation", true);
}
