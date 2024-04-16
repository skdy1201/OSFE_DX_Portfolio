#include "pch.h"
#include "CLurkerHitState.h"

#include <Engine/CAnim.h>
#include <Engine/CAnimator2D.h>
#include <Engine/CStateMachine.h>
#include <Engine/CTransform.h>

#include <Engine/CRenderComponent.h>

#include "CFieldObjScript.h"
#include "CLurkerScript.h"

CLurkerHitState::CLurkerHitState()
	: CState((UINT)STATE_TYPE::LURKERHITSTATE)
{
}

CLurkerHitState::~CLurkerHitState()
{
}

void CLurkerHitState::Enter()
{
	Lurker = BlackBoardOwner
	LurkerScript = Lurker->GetScript<CLurkerScript>();

	Player = BlackBoardPlayer
	PlayerScript = Player->GetScript<CFieldObjScript>();

	AttackTimer = (float*)GetBlackboardData(L"AttackCooldown");

	HitFX = CPrefab::GetPrefabObj(PrefabHitFX);

	Vec3 Hitposition = Lurker->Transform()->GetRelativePos();
	HitFX->Transform()->SetRelativePos(Hitposition);

	HitFX->Transform()->SetOffset(Vec2{ 0.f, -40.f });
	HitFX->Transform()->SetRelativeScale(Lurker->Transform()->GetRelativeScale() * 2);
	GamePlayStatic::SpawnGameObject(HitFX, LayerDefault);

	GamePlayStatic::Play2DSound(L"sound\\enemy_hit_heavy.wav", 1, 0.5f);

}

void CLurkerHitState::finaltick()
{
	if (LurkerScript->GetStatus().Current_HP <= 0)
	{
		Lurker->StateMachine()->GetFSM()->ChangeState(L"CLurkerDeadState");
	}

	if (HitFX->Animator2D()->GetCurAnim()->IsFinish())
	{
		//if (*AttackTimer >= 5.f)
		//{
		//	//ChangeState(L"CLurkerAttackState");
		//}
		
		
			ChangeState(L"CLurkerIdleState");
		
	}

}

void CLurkerHitState::Exit()
{
	LurkerScript->SetHit(false);
}
