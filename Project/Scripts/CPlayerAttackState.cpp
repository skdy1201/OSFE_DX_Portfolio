#include "pch.h"
#include "CPlayerAttackState.h"


#include "CFieldScript.h"
#include "CFieldObjScript.h"
#include "CProjectileScript.h"

#include <Engine/CAnimator2D.h>
#include <Engine/CAnim.h>


int CPlayerAttackState::AnimationCount = 2;

CPlayerAttackState::CPlayerAttackState()
	: CState((UINT)STATE_TYPE::PLAYERATTACKSTATE)
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
	GamePlayStatic::Play2DSound(L"sound\\mark_02.wav", 1, 0.5f);

	pProjScript->SetDir(Vec3(1.f, 0.f, 0.f));

	GamePlayStatic::SpawnGameObject(Bullet, LayerPlayerAttack);

	AttackTimer = 0.f;

	++AnimationCount;
	AnimationCount %= 3;


	if(AnimationCount == 0)
	Player->Animator2D()->Play(PlayerAttack0, false);
	else if (AnimationCount == 1)
		Player->Animator2D()->Play(PlayerAttack1, false);
	else
		Player->Animator2D()->Play(PlayerAttack2, false);

}

void CPlayerAttackState::finaltick()
{
	if (KEY_PRESSED((KEY::E)) && AttackTimer >= 0.2f)
	{
		Bullet = CPrefab::GetPrefabObj(PrefabPlayerBullet);


		CProjectileScript* pProjScript = Bullet->GetScript<CProjectileScript>();
		Proj_Struct info = pProjScript->GetInfo();

		pProjScript->Shoot(Player, Field, Vec2(100.f, 0.f), info);
		GamePlayStatic::Play2DSound(L"sound\\mark_02.wav", 1, 0.5f);

		pProjScript->SetDir(Vec3(1.f, 0.f, 0.f));

		GamePlayStatic::SpawnGameObject(Bullet, LayerPlayerAttack);

		AttackTimer = 0.f;

		++AnimationCount;
		AnimationCount %= 3;

		if (AnimationCount ==0 && Player->Animator2D()->GetCurAnim()->IsFinish())
		{
			Player->Animator2D()->Play(PlayerAttack0,false);
		}
		else if (AnimationCount == 1 && Player->Animator2D()->GetCurAnim()->IsFinish())
		{
			Player->Animator2D()->Play(PlayerAttack1, false);
		}
		else if (AnimationCount == 2 && Player->Animator2D()->GetCurAnim()->IsFinish())
		{
			Player->Animator2D()->Play(PlayerAttack2, false);

		}


	}

	AttackTimer += DT;

	if(KEY_RELEASED(KEY::E))
	{
		Player->StateMachine()->GetFSM()->ChangeState(L"CPlayerIdleState");
	}

	if (KEY_TAP(KEY::UP) && PlayerScript->GetOwnerIdx().y <= 2)
	{
		*(Vec2*)GetBlackboardData(L"NextIdx") = Vec2(0, 1);
		Player->Animator2D()->Play(L"SaffronMoveUp", false);


		Player->StateMachine()->GetFSM()->ChangeState(L"CPlayerMoveState");
	}

	if (KEY_TAP(KEY::DOWN) && PlayerScript->GetOwnerIdx().y >= 1)
	{
		*(Vec2*)GetBlackboardData(L"NextIdx") = Vec2(0, -1);
		Player->Animator2D()->Play(L"SaffronMoveDown", false);


		Player->StateMachine()->GetFSM()->ChangeState(L"CPlayerMoveState");
	}

	if (KEY_TAP(KEY::LEFT) && PlayerScript->GetOwnerIdx().x >= 5)
	{
		*(Vec2*)GetBlackboardData(L"NextIdx") = Vec2(-1, 0);
		Player->Animator2D()->Play(L"SaffronMoveBack", false);

		Player->StateMachine()->GetFSM()->ChangeState(L"CPlayerMoveState");
	}

	if (KEY_TAP(KEY::RIGHT) && PlayerScript->GetOwnerIdx().x <= 6)
	{
		*(Vec2*)GetBlackboardData(L"NextIdx") = Vec2(1, 0);
		Player->Animator2D()->Play(L"SaffronMoveFront", false);

		Player->StateMachine()->GetFSM()->ChangeState(L"CPlayerMoveState");
	}

	if (KEY_TAP(KEY::E))
	{
		Player->StateMachine()->GetFSM()->ChangeState(L"CPlayerAttackState");
	}
}

void CPlayerAttackState::Exit()
{
}
