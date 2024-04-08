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
	//SniperShoot ���������ȹٲ�ϱ� enter���� ���� �ʿ䰡 ����
	// �Ʊ� �ִϸ��̼ǵ� ���ݴܰ迡�� �� �ʿ䰡 ����. �׳� script�� ���� ��Ʈ��
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

		//�ۿ��� ������ ������ �� �ֵ��� �ϴ� ���� �߿��ϴ�.
		//�׳� ���� �Ϲ��� ����.
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
