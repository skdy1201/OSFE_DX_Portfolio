#include "pch.h"
#include "CSniperAttackState.h"

#include <Engine/CAnimator2D.h>
#include <Engine/CAnim.h>

#include <Engine/CMeshRender.h>
#include <Engine/CMaterial.h>

#include "CFieldObjScript.h"
#include "CSniperProj.h"



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
	Sniper = BlackBoardOwner
	AnimatorObject = (CGameObject*)GetBlackboardData(L"ChildAnim");

	OwnerScript = Sniper->GetScript<CFieldObjScript>();

	AttackTimer = AttackCooldown
	MoveTimer = MoveCooldown



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
	if (OwnerScript->GetStatus().Current_HP <= 0)
	{
		Sniper->StateMachine()->GetFSM()->ChangeState(L"CSniperDeadState");
	}

	if (Sniper->Animator2D()->GetCurAnim()->IsFinish())
	{
		*AttackTimer = 0.f;

		CGameObject* Bullet = CPrefab::GetPrefabObj(PrefabSniperBullet);
		CSniperProj* pSniperPorj = Bullet->GetScript<CSniperProj>();

		CFieldScript* CurField = Sniper->GetScript<CFieldObjScript>()->GetField();
		Proj_Struct Info = pSniperPorj->GetInfo();

		pSniperPorj->Shoot(Sniper, CurField, Vec2(-40.f, 71.f), Info);

		//밖에서 방향을 설정할 수 있도록 하는 것이 중요하다.
		//그냥 쓰면 일반을 쓰자.
		pSniperPorj->SetDir(Vec3{ -1.f, 0.f, 0.f });
		GamePlayStatic::SpawnGameObject(Bullet, LayerMonsterAttack);

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
	*MoveTimer -= 2.f;
}
