#include "pch.h"
#include "CPlayerIdleState.h"

#include "CFieldScript.h"
#include "CFieldObjScript.h"
#include "CProjectileScript.h"

#include <Engine/CAnimator2D.h>
#include <Engine/CAnim.h>

#include <Engine/CAnim.h>
#include <Engine/CAnimator2D.h>

CPlayerIdleState::CPlayerIdleState()
	: CState((UINT)STATE_TYPE::PLAYERIDLESTATE)
	, AttackTimer(0.f)
	, AttackRelayTimer(0.f)
{
}

CPlayerIdleState::~CPlayerIdleState()
{
}

void CPlayerIdleState::Enter()
{
	Player = BlackBoardPlayer;
	PlayerScript = Player->GetScript<CFieldObjScript>();
	Field = PlayerScript->GetField();

	Player->Animator2D()->Play(L"SaffronIdle", true);

	AttackTimer = 0.03f;
}



void CPlayerIdleState::finaltick()
{
	if (KEY_TAP(KEY::UP))
	{
		*(Vec2*)GetBlackboardData(L"NextIdx") = Vec2(0, 1);
		Player->Animator2D()->Play(L"SaffronMoveUp", false);


		Player->StateMachine()->GetFSM()->ChangeState(L"CPlayerMoveState");
	}

	if (KEY_TAP(KEY::DOWN))
	{
		*(Vec2*)GetBlackboardData(L"NextIdx") = Vec2(0, -1);
		Player->Animator2D()->Play(L"SaffronMoveDown", false);


		Player->StateMachine()->GetFSM()->ChangeState(L"CPlayerMoveState");
	}

	if (KEY_TAP(KEY::LEFT))
	{
		*(Vec2*)GetBlackboardData(L"NextIdx") = Vec2(-1, 0);
		Player->Animator2D()->Play(L"SaffronMoveBack", false);

		Player->StateMachine()->GetFSM()->ChangeState(L"CPlayerMoveState");
	}

	if (KEY_TAP(KEY::RIGHT))
	{
		*(Vec2*)GetBlackboardData(L"NextIdx") = Vec2(1, 0);
		Player->Animator2D()->Play(L"SaffronMoveFront", false);

		Player->StateMachine()->GetFSM()->ChangeState(L"CPlayerMoveState");
	}


	Shoot(DT);

}

void CPlayerIdleState::Exit()
{
}


void CPlayerIdleState::Shoot(float _Dt)
{
	CGameObject* GameObj;
	GameObj = CPrefab::GetPrefabObj(L"prefab\\PlayerBullet.pref");

	CProjectileScript* pProjScript = GameObj->GetScript<CProjectileScript>();
	Proj_Struct info = pProjScript->GetInfo();

	pProjScript->Shoot(Player, Field, Vec2(10.f, 0.f), info);
	pProjScript->SetDir(Vec3(1.f, 0.f, 0.f));

	if (KEY_TAP(KEY::E) && AttackTimer >= 0.03f)
	{
		GamePlayStatic::SpawnGameObject(GameObj, 0);

		AttackTimer = 0.f;
	}
	else if(KEY_PRESSED((KEY::E)) && AttackTimer >= 0.1f)
	{
		CAnim* pAnim;

			GamePlayStatic::SpawnGameObject(GameObj, 0);
			AttackTimer = 0.f;
	}

	AttackTimer += _Dt;
}