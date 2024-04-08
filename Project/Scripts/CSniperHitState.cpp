#include "pch.h"
#include "CSniperHitState.h"

#include <Engine/CAnim.h>
#include <Engine/CAnimator2D.h>
#include <Engine/CStateMachine.h>
#include <Engine/CTransform.h>

#include <Engine/CRenderComponent.h>

#include "CFieldObjScript.h"
#include "CSniperScript.h"


CSniperHitState::CSniperHitState()
	: CState((UINT)STATE_TYPE::SNIPERHITSTATE)
{
}

CSniperHitState::~CSniperHitState()
{

}

void CSniperHitState::Enter()
{
	Sniper = BlackBoardOwner
	SniperScript = Sniper->GetScript<CSniperScript>();

	Player = BlackBoardPlayer
	PlayerScript = Player->GetScript<CFieldObjScript>();

	CurRow = *(int*)GetBlackboardData(L"Current Row");
	PlayerRow = (int)PlayerScript->GetOwnerIdx().y;

	HitFX = CPrefab::GetPrefabObj(PrefabHitFX);

	Vec3 Hitposition = Sniper->Transform()->GetRelativePos();
	HitFX->Transform()->SetRelativePos(Hitposition);

	HitFX->Transform()->SetOffset(Vec2{ 0.f, 0.f });
	HitFX->Transform()->SetRelativeScale(Sniper->Transform()->GetRelativeScale() * 2);
	GamePlayStatic::SpawnGameObject(HitFX, LayerDefault);

	Sniper->GetRenderComopnent()->GetDynamicMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, 0);


}

void CSniperHitState::finaltick()
{
	if(HitFX->Animator2D()->GetCurAnim()->IsFinish())
	{
		Sniper->StateMachine()->GetFSM()->ChangeState(L"CSniperIdleState");
	}

	AttackTimer = (float*)GetBlackboardData(L"AttackCooldown");

	int PlayerRow = (int)PlayerScript->GetOwnerIdx().y;
	int SniperRow = *(int*)GetBlackboardData(L"Current Row");

	if (PlayerRow == SniperRow && *AttackTimer >= 5.f)
	{
		ChangeState(L"CSniperAttackState");
	}

}

void CSniperHitState::Exit()
{
	Sniper->GetRenderComopnent()->GetDynamicMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, 1);
	SniperScript->SetHit(false);
	

}
