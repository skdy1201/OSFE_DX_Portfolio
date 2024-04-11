#include "pch.h"
#include "CHitAnimationModule.h"

#include <Engine/CAnim.h>
#include <Engine/CAnimator2D.h>
#include "CRandomMgr.h"

CHitAnimationModule::CHitAnimationModule()
	: CAnimatorModule((UINT)SCRIPT_TYPE::HITANIMATIONMODULE)
{
	MaxBound = HitFXRandomcount;
	MaxPos = HitFXRamdonPosScale;
}

CHitAnimationModule::~CHitAnimationModule()
{
}

void CHitAnimationModule::SetRandomPos()
{
	Vec3 RandomPosition = pObj->Transform()->GetRelativePos();

	int random = CRandomMgr::GetInst()->GetRandom(MaxPos);
	random -= HitFXRamdonPosScale;

	RandomPosition.x += random;

	random = CRandomMgr::GetInst()->GetRandom(MaxPos);
	random -= HitFXRamdonPosScale;

	RandomPosition.y += random;

	pObj->Transform()->SetRelativePos(RandomPosition);
}

void CHitAnimationModule::SetRandomScale()
{
	int random = CRandomMgr::GetInst()->GetRandom(MaxPos);

	Vec3 RandomScale = pObj->Transform()->GetRelativeScale();
	random -= HitFXRamdonPosScale;
	RandomScale.x += random;

	random = CRandomMgr::GetInst()->GetRandom(MaxPos);
	random -= HitFXRamdonPosScale;
	RandomScale.y += random;

	pObj->Transform()->SetRelativeScale(RandomScale);
}

void CHitAnimationModule::begin()
{
	CAnimatorModule::begin();

	SetRandomPos();

	SetRandomScale();

	int random = CRandomMgr::GetInst()->GetRandom(MaxBound);

	switch (random)
	{
	case 0:
		OwnerAnimator->Play(HitFX0, false);
		break;
	case 1:
		OwnerAnimator->Play(HitFX1, false);
		break;
	case 2:
		OwnerAnimator->Play(HitFX2, false);
		break;
	}
}

void CHitAnimationModule::tick()
{
	if(OwnerAnimator->GetCurAnim()->IsFinish())
	{
		pObj->Destroy();
	}
}

void CHitAnimationModule::SaveToFile(ofstream& _File)
{
}

void CHitAnimationModule::LoadFromFile(ifstream& _File)
{
}
