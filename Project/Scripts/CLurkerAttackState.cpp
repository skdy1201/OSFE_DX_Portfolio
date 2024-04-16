#include "pch.h"
#include "CLurkerAttackState.h"

#include <Engine/CAnimator2D.h>
#include <Engine/CAnim.h>

#include <Engine/CMeshRender.h>
#include <Engine/CMaterial.h>

#include "CFieldObjScript.h"
#include "CFieldScript.h"
#include "CLurkerScript.h"

CLurkerAttackState::CLurkerAttackState()
	: CState((UINT)STATE_TYPE::LURKERATTACKSTATE)
{
}

CLurkerAttackState::~CLurkerAttackState()
{
}

void CLurkerAttackState::Enter()
{
	Lurker = BlackBoardOwner

	OwnerScript = Lurker->GetScript<CLurkerScript>();

	field = OwnerScript->GetField();

	CGameObject* player = BlackBoardPlayer;
	PlayerScript = player->GetScript<CFieldObjScript>();

	AttackTimer = AttackCooldown

	SpawnCOUNT = 4;

	Warning = CAssetMgr::GetInst()->Load<CPrefab>(PrefabTileAnimation, PrefabTileAnimation);
	//LurkerShot = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\LurkerShot.pref", L"prefab\\LurkerShot.pref");


}

void CLurkerAttackState::finaltick()
{
	CGameObject* warn = Warning->Instantiate();
	CGameObject* shot = LurkerShot->Instantiate();

	float playery = PlayerScript->GetOwnerIdx().y;

	if (SpawnCOUNT == 4)
	{
		Vec2 spawnidx = {};
		spawnidx.x = 7;
		spawnidx.y = playery;
		Vec3 Pos =field->GetTilePosition(spawnidx);

		Pos.z += 50.f;

		warn->Transform()->SetRelativePos(Pos);
		shot->Transform()->SetRelativePos(Pos);
		
		GamePlayStatic::SpawnGameObject(warn, 0);
		GamePlayStatic::SpawnGameObject(shot, LayerMonsterAttack, 2.1f);
		--SpawnCOUNT;
	}
	else if (SpawnCOUNT == 3)
	{
		Vec2 spawnidx = Vec2((6, playery));
		Vec3 Pos = field->GetTilePosition(spawnidx);

		warn->Transform()->SetRelativePos(Pos);
		shot->Transform()->SetRelativePos(Pos);

		GamePlayStatic::SpawnGameObject(warn, 0);
		GamePlayStatic::SpawnGameObject(shot, LayerMonsterAttack, 2.1f);
		--SpawnCOUNT;
	}
	else if (SpawnCOUNT == 2)
	{
		Vec2 spawnidx = Vec2((5, playery));
		Vec3 Pos = field->GetTilePosition(spawnidx);

		warn->Transform()->SetRelativePos(Pos);
		shot->Transform()->SetRelativePos(Pos);

		GamePlayStatic::SpawnGameObject(warn, 0);
		GamePlayStatic::SpawnGameObject(shot, LayerMonsterAttack, 2.1f);
		--SpawnCOUNT;
	}
	else if (SpawnCOUNT == 1)
	{
		Vec2 spawnidx = Vec2((4., playery));
		Vec3 Pos = field->GetTilePosition(spawnidx);

		warn->Transform()->SetRelativePos(Pos);
		shot->Transform()->SetRelativePos(Pos);

		GamePlayStatic::SpawnGameObject(warn, 0);
		GamePlayStatic::SpawnGameObject(shot, LayerMonsterAttack, 2.1f);
		--SpawnCOUNT;
	}


	if (SpawnCOUNT == 0)
		ChangeState(L"CLurkerIdleState");

}

void CLurkerAttackState::Exit()
{
	*AttackTimer = 0.f;
}
