#include "pch.h"
#include "CSniperAttackState.h"

#include <Engine/CAnimator2D.h>
#include <Engine/CAnim.h>

#include <Engine/CMeshRender.h>
#include <Engine/CMaterial.h>


CSniperAttackState::CSniperAttackState()
	: CState((UINT)STATE_TYPE::SNIPERATTACKSTATE)
{
	//SniperShoot 프리팹은안바뀌니까 enter에서 가질 필요가 없고
	// 아까 애니메이션도 공격단계에서 할 필요가 없다. 그냥 script가 갖고 컨트롤
}

CSniperAttackState::~CSniperAttackState()
{
}

void CSniperAttackState::Enter()
{
	Sniper = (CGameObject*)GetBlackboardData(L"Owner");
	AnimatorObject = (CGameObject*)GetBlackboardData(L"ChildAnim");

	AttackTime = (float*)GetBlackboardData((L"AttackCooldown"));



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
		*AttackTime = 0.f;
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
