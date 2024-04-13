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

	OwnerAnimator->Play(L"TileBreakWarning");

}

void CChangeRedModule::tick()
{
	ChangeTime += DT;

	if(ChangeTime >= 0.05f)
	{
		ChangeColorR = 1.f;
		ChangeColorG = 0.f;
		ChangeColorB = 0.f;
		this->GetOwner()->GetRenderComopnent()->GetDynamicMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_0, ChangeColorR);
		this->GetOwner()->GetRenderComopnent()->GetDynamicMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_1, ChangeColorG);
		this->GetOwner()->GetRenderComopnent()->GetDynamicMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_2, ChangeColorB);
	}

	else if(ChangeTime >= 0.07f)
	{

		ChangeColorR = 1.f;
		ChangeColorG = 0.f;
		ChangeColorB = 0.f;
		this->GetOwner()->GetRenderComopnent()->GetDynamicMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_0, ChangeColorR);
		this->GetOwner()->GetRenderComopnent()->GetDynamicMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_1, ChangeColorG);
		this->GetOwner()->GetRenderComopnent()->GetDynamicMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_2, ChangeColorB);
	}

	else if (ChangeTime >= 0.2f)
	{

		ChangeColorR = 1.f;
		ChangeColorG = 1.f;
		ChangeColorB = 0.f;
		this->GetOwner()->GetRenderComopnent()->GetDynamicMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_0, ChangeColorR);
		this->GetOwner()->GetRenderComopnent()->GetDynamicMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_1, ChangeColorG);
		this->GetOwner()->GetRenderComopnent()->GetDynamicMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_2, ChangeColorB);
	}

	else if (ChangeTime >= 0.25f)
	{

		ChangeColorR = 0.f;
		ChangeColorG = 0.f;
		ChangeColorB = 1.f;
		this->GetOwner()->GetRenderComopnent()->GetDynamicMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_0, ChangeColorR);
		this->GetOwner()->GetRenderComopnent()->GetDynamicMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_1, ChangeColorG);
		this->GetOwner()->GetRenderComopnent()->GetDynamicMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_2, ChangeColorB);
	}

	if(OwnerAnimator->GetCurAnim()->IsFinish())
	{
		pObj->Destroy();
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
