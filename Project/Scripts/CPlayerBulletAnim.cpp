#include "pch.h"
#include "CPlayerBulletAnim.h"

#include <Engine/CAnim.h>

CPlayerBulletAnim::CPlayerBulletAnim()
	: CAnimatorModule((UINT)SCRIPT_TYPE::ANIMATORMODULE)
{

}

CPlayerBulletAnim::~CPlayerBulletAnim()
{
}

void CPlayerBulletAnim::begin()
{
	pObj = GetOwner();
	OwnerAnimator = pObj->Animator2D();
	AnimName = BulletBasicCast;
	count = 1;

	pObj->Transform()->SetOffset(Vec2{ 0.f, 80.f });

	OwnerAnimator->PlayModule(AnimName, count);
}

void CPlayerBulletAnim::tick()
{

	if(count == 0 && OwnerAnimator->GetCurAnim()->IsFinish())
	{
		pObj->Destroy();
	}
	else if(count > 0 && OwnerAnimator->GetCurAnim()->IsFinish())
	{
		OwnerAnimator->PlayModule(AnimName, count);
	}
}

void CPlayerBulletAnim::SaveToFile(ofstream& _File)
{
	CAnimatorModule::SaveToFile(_File);
}

void CPlayerBulletAnim::LoadFromFile(ifstream& _File)
{
	CAnimatorModule::LoadFromFile(_File);
}
