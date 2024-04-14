#include "pch.h"
#include "CTerraAttackState.h"

#include <Engine/CAnim.h>

#include "CFieldObjScript.h"
#include "CFieldScript.h"
#include "Terraform.h"
#include "CRandomMgr.h"

CTerraAttackState::CTerraAttackState()
	: CState((UINT)STATE_TYPE::TERRAATTACKSTATE)
	, bAttack(false)
{
}

CTerraAttackState::~CTerraAttackState()
{
}

void CTerraAttackState::Enter()
{
	Terra = BlackBoardOwner
	TerraScript = Terra->GetScript<CFieldObjScript>();

	AnimatorObject = CAssetMgr::GetInst()->Load<CPrefab>(PrefabTileAnimation, PrefabTileAnimation);

	AttackTimer = AttackCooldown
		MoveTimer = MoveCooldown

		m_Terraform = new Terraform;

		AttackPattern = 0; //CRandomMgr::GetInst()->GetRandom(3);

	switch (AttackPattern)
	{
	case 0:
		Attack1();
		break;
	case 1:
		Attack2();
		break;
	case 2:
		Attack3();
		break;
	}
}

void CTerraAttackState::Attack1()
{
	Vec2 Idx = Vec2{ 4, 0 };
	Vec3 Position = TerraScript->GetField()->GetTilePosition(Idx);

	CGameObject* animation = AnimatorObject->Instantiate();

	animation->Transform()->SetRelativePos(Position);
	GamePlayStatic::SpawnGameObject(animation, 0);

	CheckAnimation[0] = animation;

	Idx = Vec2{ 7, 0 };
	Position = TerraScript->GetField()->GetTilePosition(Idx);

	animation = AnimatorObject->Instantiate();

	animation->Transform()->SetRelativePos(Position);
	GamePlayStatic::SpawnGameObject(animation, 0);

	CheckAnimation[1] = animation;

	Idx = Vec2{ 4, 3 };
	Position = TerraScript->GetField()->GetTilePosition(Idx);

	animation = AnimatorObject->Instantiate();

	animation->Transform()->SetRelativePos(Position);
	GamePlayStatic::SpawnGameObject(animation, 0);

	CheckAnimation[2] = animation;


	Idx = Vec2{ 7, 3 };
	Position = TerraScript->GetField()->GetTilePosition(Idx);

	animation = AnimatorObject->Instantiate();

	animation->Transform()->SetRelativePos(Position);
	GamePlayStatic::SpawnGameObject(animation, 0);

	CheckAnimation[3] = animation;

	bAttack = true;

}

void CTerraAttackState::Attack2()
{
}

void CTerraAttackState::Attack3()
{
}



void CTerraAttackState::finaltick()
{

	if(CheckEndAnim() == true && AttackPattern == 0)
	{
		m_Terraform->SetCaster(Terra);
		m_Terraform->cast(TerraScript->GetOwnerIdx());
		bAttack = false;
	}

	if(bAttack == false)
	ChangeState(L"CTerraIdleState");

}

bool CTerraAttackState::CheckEndAnim()
{
	for(int i = 0; i < 4; ++i)
	{
		if (CheckAnimation[i]->IsDead())
			continue;
		else
			return false;
	}

	return true;
}

void CTerraAttackState::Exit()
{
	delete m_Terraform;
	*AttackTimer = 0.f;
}