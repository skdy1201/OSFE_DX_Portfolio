#include "pch.h"
#include "CPlayerAttackState.h"


#include "CFieldScript.h"
#include "CFieldObjScript.h"
#include "CProjectileScript.h"

#include <Engine/CAnimator2D.h>
#include <Engine/CAnim.h>

CPlayerAttackState::CPlayerAttackState()
	: CState((UINT)STATE_TYPE::PLAYERATTACKSTATE)
	, AnimationCount(0)
{
}

CPlayerAttackState::~CPlayerAttackState()
{
}


void CPlayerAttackState::Enter()
{
	Player = BlackBoardPlayer;
	PlayerScript = Player->GetScript<CFieldObjScript>();
	Field = PlayerScript->GetField();

	AttackTimer = 0.02f;

	Bullet = CPrefab::GetPrefabObj(PrefabPlayerBullet);

	CProjectileScript* pProjScript = Bullet->GetScript<CProjectileScript>();
	Proj_Struct info = pProjScript->GetInfo();

	pProjScript->Shoot(Player, Field, Vec2(100.f, 0.f), info);
	pProjScript->SetDir(Vec3(1.f, 0.f, 0.f));

	GamePlayStatic::SpawnGameObject(Bullet, LayerPlayerAttack);

	AttackTimer = 0.f;
	Player->Animator2D()->Play(PlayerAttack1, false);
	
}

void CPlayerAttackState::finaltick()
{
	if (KEY_PRESSED((KEY::E)) && AttackTimer >= 0.17f)
	{
		Bullet = CPrefab::GetPrefabObj(PrefabPlayerBullet);

		CProjectileScript* pProjScript = Bullet->GetScript<CProjectileScript>();
		Proj_Struct info = pProjScript->GetInfo();

		pProjScript->Shoot(Player, Field, Vec2(100.f, 0.f), info);
		pProjScript->SetDir(Vec3(1.f, 0.f, 0.f));

		GamePlayStatic::SpawnGameObject(Bullet, LayerPlayerAttack);

		AttackTimer = 0.f;
		++AnimationCount;

		AnimationCount %= 3;

		if (AnimationCount == 1 && Player->Animator2D()->GetCurAnim()->IsFinish())
		{
			Player->Animator2D()->Play(PlayerAttack2, false);
		}
		else if (AnimationCount == 2 && Player->Animator2D()->GetCurAnim()->IsFinish())
		{
			Player->Animator2D()->Play(PlayerAttack3, false);
		}
		else if (AnimationCount == 0 && Player->Animator2D()->GetCurAnim()->IsFinish())
		{
			Player->Animator2D()->Play(PlayerAttack1, false);

		}

	}

	AttackTimer += DT;

	if(KEY_RELEASED(KEY::E))
	{
		Player->StateMachine()->GetFSM()->ChangeState(L"CPlayerIdleState");
	}
}

void CPlayerAttackState::Exit()
{
}
