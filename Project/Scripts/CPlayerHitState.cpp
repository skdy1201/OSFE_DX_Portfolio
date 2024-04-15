#include "pch.h"
#include "CPlayerHitState.h"

#include <Engine/CAnim.h>

#include "CFieldObjScript.h"

CPlayerHitState::CPlayerHitState()
	: CState((UINT)STATE_TYPE::PLAYERHITSTATE)
	, IsRender(true)
	, Timer(0.2f)
{
}

CPlayerHitState::~CPlayerHitState()
{
}

void CPlayerHitState::Enter()
{
	Player = BlackBoardPlayer;
	PlayerScript = Player->GetScript<CFieldObjScript>();
	Field = PlayerScript->GetField();

	HitFX = CPrefab::GetPrefabObj(PrefabHitFX);

	Vec3 Hitposition = Player->Transform()->GetRelativePos();
	HitFX->Transform()->SetRelativePos(Hitposition);

	HitFX->Transform()->SetOffset(Vec2{ 0.f, -60.f });
	HitFX->Transform()->SetRelativeScale(Player->Transform()->GetRelativeScale() * 2);
	GamePlayStatic::SpawnGameObject(HitFX, LayerDefault);

	GamePlayStatic::Play2DSound(L"sound\\player_hit_heavy.wav", 1, 0.5f);
	Player->Animator2D()->Play(PlayerHit, false);

	Timer = 0.5f;
}

void CPlayerHitState::finaltick()
{
	if (Player->Animator2D()->GetCurAnim()->IsFinish())
		ChangeState(L"CPlayerIdleState");

	Timer -= DT;

	if(Timer >= 0.f)
	{
		IsRender = IsRender ? true : false;
		Player->MeshRender()->SetRenderPossible(IsRender);
	}
}

void CPlayerHitState::Exit()
{
	
	PlayerScript->SetHit(false);
}
