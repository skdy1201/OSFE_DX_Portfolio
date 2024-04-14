#include "pch.h"
#include "CChangeRedModule.h"

#include <Engine/CAnim.h>

CChangeRedModule::CChangeRedModule()
	: CAnimatorModule((UINT)SCRIPT_TYPE::CHANGEREDMODULE)
{
}

CChangeRedModule::~CChangeRedModule()
{
}

void CChangeRedModule::begin()
{
	CAnimatorModule::begin();

	ChangeColorR = 0.f;
	ChangeColorG = 0.f;
	ChangeColorB = 0.f;

	OwnerAnimator->Play(L"TileWarning", false);

}

void CChangeRedModule::tick()
{
	if(OwnerAnimator->GetCurAnim()->IsFinish())
	{
		GamePlayStatic::DestroyGameObject(pObj);
	}
}

void CChangeRedModule::SaveToFile(ofstream& _File)
{
	CAnimatorModule::SaveToFile(_File);
}

void CChangeRedModule::LoadFromFile(ifstream& _File)
{
	CAnimatorModule::LoadFromFile(_File);
}
