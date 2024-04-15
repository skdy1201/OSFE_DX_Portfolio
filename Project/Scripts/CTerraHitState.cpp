#include "pch.h"
#include "CTerraHitState.h"

#include "CTerraScript.h"

#include <Engine/CAnimator2D.h>
#include <Engine/CAnim.h>

CTerraHitState::CTerraHitState()
	: CState((UINT)STATE_TYPE::TERRAHITSTATE)
{
}

CTerraHitState::~CTerraHitState()
{

}

void CTerraHitState::Enter()
{

	Terra = this->GetFSM()->GetStateMachine()->GetOwner();
	TerraScript = Terra->GetScript<CTerraScript>();


	HitFX = CPrefab::GetPrefabObj(PrefabHitFX);

	Vec3 Hitposition = Terra->Transform()->GetRelativePos();
	HitFX->Transform()->SetRelativePos(Hitposition);

	HitFX->Transform()->SetOffset(Vec2{ 0.f, -60.f });
	HitFX->Transform()->SetRelativeScale(Terra->Transform()->GetRelativeScale() * 2);
	GamePlayStatic::SpawnGameObject(HitFX, LayerDefault);

	GamePlayStatic::Play2DSound(L"sound\\enemy_hit_heavy.wav", 1, 0.5f);

	MoveTimer = (float*)GetBlackboardData(L"MoveCooldown");

	Terra->Animator2D()->Play(L"TerraHit"), false;
}

void CTerraHitState::finaltick()
{
	if (HitFX->Animator2D()->GetCurAnim()->IsFinish())
	{
		Terra->StateMachine()->GetFSM()->ChangeState(L"CTerraIdleState");
	}

	if(*MoveTimer >= 20.f)
	{
		ChangeState(L"CTerraMoveState");
	}
}



void CTerraHitState::Exit()
{
	TerraScript->SetHit(false);

}
