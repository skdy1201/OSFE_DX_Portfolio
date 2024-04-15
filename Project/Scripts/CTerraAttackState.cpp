#include "pch.h"
#include "CTerraAttackState.h"

#include <Engine/CAnim.h>

#include "CDiagBeam.h"
#include "CFieldObjScript.h"
#include "CFieldScript.h"
#include "Terraform.h"
#include "DiagBeamMagic.h"
#include "BossDiscMagic.h"
#include "CRandomMgr.h"

CTerraAttackState::CTerraAttackState()
	: CState((UINT)STATE_TYPE::TERRAATTACKSTATE)
	, bAttack(false)
	, IsExit(false)
{
}

CTerraAttackState::~CTerraAttackState()
{
	if(!IsExit)
	{
		delete m_Terraform;
		delete m_DiagBeam;
		delete m_Disc;
	}
}

void CTerraAttackState::Enter()
{
	Terra = BlackBoardOwner
	TerraScript = Terra->GetScript<CFieldObjScript>();

	AnimatorObject = CAssetMgr::GetInst()->Load<CPrefab>(PrefabTileAnimation, PrefabTileAnimation);

	AttackTimer = AttackCooldown
		MoveTimer = MoveCooldown

	m_Terraform = new Terraform;
	m_DiagBeam = new DiagBeamMagic;
	m_Disc = new BossDiscMagic;
	
		AttackPattern = CRandomMgr::GetInst()->GetRandom(3);

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
	Vec2 Idx = Vec2{ 4, 0 };
	Vec3 Position = TerraScript->GetField()->GetTilePosition(Idx);

	CGameObject* animation = AnimatorObject->Instantiate();

	animation->Transform()->SetRelativePos(Position);
	GamePlayStatic::SpawnGameObject(animation, 0);

	CheckAnimation[0] = animation;

	Idx = Vec2{ 7, 0 };
	Position = TerraScript->GetField()->GetTilePosition(Idx);

	animation = AnimatorObject->Instantiate();

	animation->Transform()->SetRelativePos(Position);
	GamePlayStatic::SpawnGameObject(animation, 0);

	CheckAnimation[1] = animation;

	Idx = Vec2{ 4, 3 };
	Position = TerraScript->GetField()->GetTilePosition(Idx);

	animation = AnimatorObject->Instantiate();

	animation->Transform()->SetRelativePos(Position);
	GamePlayStatic::SpawnGameObject(animation, 0);

	CheckAnimation[2] = animation;


	Idx = Vec2{ 7, 3 };
	Position = TerraScript->GetField()->GetTilePosition(Idx);

	animation = AnimatorObject->Instantiate();

	animation->Transform()->SetRelativePos(Position);
	GamePlayStatic::SpawnGameObject(animation, 0);

	CheckAnimation[3] = animation;

	Terra->Animator2D()->Play(L"TerraAttack1", false);

	GamePlayStatic::Play2DSound(L"sound\\beam_shot_low.wav", 1, 0.5f, true);
	GamePlayStatic::Play2DSound(L"sound\\beam_shot_low.wav", 1, 0.5f, true);
	GamePlayStatic::Play2DSound(L"sound\\beam_shot_low.wav", 1, 0.5f, true);
	GamePlayStatic::Play2DSound(L"sound\\beam_shot_low.wav", 1, 0.5f, true);

	bAttack = true;

}

void CTerraAttackState::Attack2()
{
	Vec2 Idx = Vec2{ 5, 3 };
	Vec3 Position = TerraScript->GetField()->GetTilePosition(Idx);

	CGameObject* animation = AnimatorObject->Instantiate();

	animation->Transform()->SetRelativePos(Position);
	GamePlayStatic::SpawnGameObject(animation, 0);

	CheckAnimation[0] = animation;

	 Idx = Vec2{ 6, 3 };
	 Position = TerraScript->GetField()->GetTilePosition(Idx);

	 animation = AnimatorObject->Instantiate();

	animation->Transform()->SetRelativePos(Position);
	GamePlayStatic::SpawnGameObject(animation, 0);

	CheckAnimation[1] = animation;

	Idx = Vec2{ 5, 2 };
	Position = TerraScript->GetField()->GetTilePosition(Idx);

	animation = AnimatorObject->Instantiate();

	animation->Transform()->SetRelativePos(Position);
	GamePlayStatic::SpawnGameObject(animation, 0);

	CheckAnimation[2] = animation;

	Idx = Vec2{ 6, 2 };
	Position = TerraScript->GetField()->GetTilePosition(Idx);

	animation = AnimatorObject->Instantiate();

	animation->Transform()->SetRelativePos(Position);
	GamePlayStatic::SpawnGameObject(animation, 0);

	Terra->Animator2D()->Play(L"TerraAttack3-2", true);

	GamePlayStatic::Play2DSound(L"sound\\beam_impact.wav", 1, 0.5f, true);


	CheckAnimation[3] = animation;
	bAttack = true;
}

void CTerraAttackState::Attack3()
{
	for(int i = 0; i < 2; ++i)
	{
		DiscIdx[i].x = CRandomMgr::GetInst()->GetRandom(4);
		DiscIdx[i].x += 4;

		DiscIdx[i].y = CRandomMgr::GetInst()->GetRandom(4);

	}

	Vec2 Idx = DiscIdx[0];
	Vec3 Position = TerraScript->GetField()->GetTilePosition(Idx);

	CGameObject* animation = AnimatorObject->Instantiate();

	animation->Transform()->SetRelativePos(Position);
	GamePlayStatic::SpawnGameObject(animation, 0);

	CheckAnimation[0] = animation;

	Idx = DiscIdx[1];
	Position = TerraScript->GetField()->GetTilePosition(Idx);

	animation = AnimatorObject->Instantiate();

	animation->Transform()->SetRelativePos(Position);
	GamePlayStatic::SpawnGameObject(animation, 0);

	CheckAnimation[1] = animation;

	Terra->Animator2D()->Play(L"TerraAttack2", false);
	GamePlayStatic::Play2DSound(L"sound\\beam_shot_loud.wav", 1, 0.5f, true);


	bAttack = true;
}



void CTerraAttackState::finaltick()
{

	if(AttackPattern == 0)
	{
		if(this->GetFSM()->GetStateMachine()->GetOwner()->Animator2D()->GetCurAnim()->IsFinish())
			Terra->Animator2D()->Play(L"TerraIdle", true);

		if(CheckEndAnim() == true)
		{

		m_Terraform->SetCaster(Terra);
		m_Terraform->cast(TerraScript->GetOwnerIdx());
		bAttack = false;
		}
	}
	else if(AttackPattern == 1)
	{
		if (CheckEndAnim() == true)
		{
			if (this->GetFSM()->GetStateMachine()->GetOwner()->Animator2D()->GetCurAnim()->IsFinish())
				Terra->Animator2D()->Play(L"TerraIdle", true);

			m_DiagBeam->SetCaster(Terra);
			m_DiagBeam->cast(Vec2(5, 3));
			m_DiagBeam->cast(Vec2(6, 3));
			m_DiagBeam->cast(Vec2(5, 2));
			m_DiagBeam->cast(Vec2(6, 2));

			bAttack = false;
		}
	}
	else if(AttackPattern == 2)
	{
		if (this->GetFSM()->GetStateMachine()->GetOwner()->Animator2D()->GetCurAnim()->IsFinish())
			Terra->Animator2D()->Play(L"TerraIdle", true);

		if (CheckEndAnim() == true)
		{
			m_Disc->SetCaster(Terra);
			m_Disc->cast(DiscIdx[0]);
			m_Disc->cast(DiscIdx[1]);

			bAttack = false;
		}
	}


	if(bAttack == false)
	ChangeState(L"CTerraIdleState");
}

bool CTerraAttackState::CheckEndAnim()
{
	for(int i = 0; i < 4; ++i)
	{
		if (CheckAnimation[i] == nullptr || CheckAnimation[i]->IsDead())
			continue;
		else
			return false;
	}

	return true;
}

void CTerraAttackState::Exit()
{
	IsExit = true;

	delete m_Terraform;
	delete m_DiagBeam;
	delete m_Disc;
	*AttackTimer = 0.f;
}