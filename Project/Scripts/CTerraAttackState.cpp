#include "pch.h"
#include "CTerraAttackState.h"

#include "CFieldObjScript.h"
#include "CFieldScript.h"
#include "CMagic.h"
#include "CRandomMgr.h"

CTerraAttackState::CTerraAttackState()
	: CState((UINT)STATE_TYPE::TERRAATTACKSTATE)
{
}

CTerraAttackState::~CTerraAttackState()
{
}

void CTerraAttackState::Enter()
{
	Terra = BlackBoardOwner
	TerraScript = Terra->GetScript<CFieldObjScript>();

	AnimatorObject = CPrefab::GetPrefabObj(PrefabTileAnimation);

	AttackTimer = AttackCooldown
		MoveTimer = MoveCooldown

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
	//Vec2 Idx = Vec2{ 4, 0 };
	//Vec3 Position = TerraScript->GetField()->GetTilePosition(Idx);

	//CGameObject* clone = AnimatorObject->Clone();

	//clone->Transform()->SetRelativePos(Position);
	//GamePlayStatic::SpawnGameObject(clone, 0);

	//CheckAnimation[0] = clone;

	//Idx = Vec2{ 7, 0 };
	//Position = TerraScript->GetField()->GetTilePosition(Idx);

	//clone = AnimatorObject->Clone();

	//clone->Transform()->SetRelativePos(Position);
	//GamePlayStatic::SpawnGameObject(clone, 0);

	//CheckAnimation[1] = clone;

	//Idx = Vec2{ 4, 3 };
	//Position = TerraScript->GetField()->GetTilePosition(Idx);

	//clone = AnimatorObject->Clone();

	//clone->Transform()->SetRelativePos(Position);
	//GamePlayStatic::SpawnGameObject(clone, 0);

	//CheckAnimation[2] = clone;

	//Idx = Vec2{ 7, 3 };
	//Position = TerraScript->GetField()->GetTilePosition(Idx);

	//clone = AnimatorObject->Clone();
	//
	//clone->Transform()->SetRelativePos(Position);
	//GamePlayStatic::SpawnGameObject(clone, 0);

	//CheckAnimation[3] = clone;

	//int d = 0;
}

void CTerraAttackState::Attack2()
{
}

void CTerraAttackState::Attack3()
{
}

bool CTerraAttackState::checkAnimation()
{
	for (int i = 0; i < 4; ++i)
	{
		if (CheckAnimation[i] == nullptr)
			continue;
		else
			return false;
	}

	return true;
}

void CTerraAttackState::finaltick()
{
	if (checkAnimation() && AttackPattern == 0)
	{
		
	}

	ChangeState(L"CTerraIdleState");
}

void CTerraAttackState::Exit()
{
	*AttackTimer = 0.f;
}
