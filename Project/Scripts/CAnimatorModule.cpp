#include "pch.h"
#include "CAnimatorModule.h"

CAnimatorModule::CAnimatorModule()
	: CScript((UINT)SCRIPT_TYPE::ANIMATORMODULE)
{
}

CAnimatorModule::CAnimatorModule(UINT type)
	: CScript(type)
{
}

CAnimatorModule::~CAnimatorModule()
{
}

void CAnimatorModule::begin()
{
	pObj = this->GetOwner();
	OwnerAnimator = pObj->Animator2D();
}

void CAnimatorModule::tick()
{

}

void CAnimatorModule::SaveToFile(ofstream& _File)
{
}

void CAnimatorModule::LoadFromFile(ifstream& _File)
{
}
