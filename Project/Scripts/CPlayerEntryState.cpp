#include "pch.h"
#include "CPlayerEntryState.h"

#include <Engine/CStateMachine.h>

#include <Engine/CAnimator2D.h>
#include <Engine/CAnim.h>

#include <Engine/CTransform.h>

#include  <Engine/CGameObject.h>

CPlayerEntryState::CPlayerEntryState()
	: CState((UINT)STATE_TYPE::PLAYERENTRYSTATE)
	, Player(nullptr)
	, PlayerScript(nullptr)
{
}

CPlayerEntryState::~CPlayerEntryState()
{


}

void CPlayerEntryState::Enter()
{
	Player = BlackBoardPlayer

	Player->Animator2D()->Play(L"SaffronSpawn", false);

	Player->Transform()->SetOffset(Vec2{ 0.f, 10.f });

	CGameObject* obj = CPrefab::GetPrefabObj(PrefabPlayerSpawnAnim);
	obj->Transform()->SetRelativePos(Player->Transform()->GetRelativePos());
	
	GamePlayStatic::SpawnGameObject(obj, 0);
}

void CPlayerEntryState::finaltick()
{
	if (Player != nullptr && Player->Animator2D()->GetCurAnim()->GetName() == wstring(L"SaffronSpawn")
		&& Player->Animator2D()->GetCurAnim()->IsFinish())
	{
		Player->StateMachine()->GetFSM()->ChangeState(L"CPlayerIdleState");

	}
}

void CPlayerEntryState::Exit()
{
}
