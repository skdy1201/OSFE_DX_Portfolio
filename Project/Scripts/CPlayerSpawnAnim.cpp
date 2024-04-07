#include "pch.h"
#include "CPlayerSpawnAnim.h"

#include <Engine/CAnimator2D.h>
#include <Engine/CAnim.h>

CPlayerSpawnAnim::CPlayerSpawnAnim()
	: CAnimatorModule((UINT)SCRIPT_TYPE::PLAYERSPAWNANIM)
{
}

CPlayerSpawnAnim::~CPlayerSpawnAnim()
{
}

void CPlayerSpawnAnim::begin()
{
	pObj = GetOwner();
	OwnerAnimator = pObj->Animator2D();
	AnimName = SpawnEffect;
	count = 1;

	pObj->Transform()->SetOffset(Vec2{ 0.f, 0.f });

	OwnerAnimator->PlayModule(AnimName, count);
}

void CPlayerSpawnAnim::tick()
{

	if (count == 0 && OwnerAnimator->GetCurAnim()->IsFinish())
	{
		pObj->Destroy();
	}
	else if (count > 0 && OwnerAnimator->GetCurAnim()->IsFinish())
	{
		OwnerAnimator->PlayModule(AnimName, count);
	}

}

void CPlayerSpawnAnim::SaveToFile(ofstream& _File)
{
}

void CPlayerSpawnAnim::LoadFromFile(ifstream& _File)
{
}
