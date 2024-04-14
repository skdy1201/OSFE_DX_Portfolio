#include "pch.h"
#include "CManaProgrssUIScript.h"

#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>

#include "CFieldObjScript.h"

CManaProgrssUIScript::CManaProgrssUIScript()
	: CUIScript()
	, ManaRegen(0)
{
}

CManaProgrssUIScript::~CManaProgrssUIScript()
{
}

void CManaProgrssUIScript::begin()
{
	CUIScript::begin();

	pObj->MeshRender()->GetDynamicMaterial()->SetScalarParam(SCALAR_PARAM::VEC4_0, Vec4{ 0.2f, 0.6f, 0.86f, 1.f });

	Owner = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
	OwnerScript = Owner->GetScript<CFieldObjScript>();


}

void CManaProgrssUIScript::tick()
{
	MaxMana = OwnerScript->GetStatus().MP;
	CurrentMana = OwnerScript->GetStatus().Current_MP;
	ManaRegen = OwnerScript->GetStatus().Mana_Regen;

	float Percent = CurrentMana / MaxMana;

	Vec3 Scale = pObj->Transform()->GetRelativeScale();

	if(Percent >= 1.f)
	{
		Percent = 1.f;
	}

	Scale.x = Percent * ManaProgrssScaleX;

	pObj->Transform()->SetRelativeScale(Scale);

	float offsetx = Scale.x / 2;
	Vec2 Offset = { offsetx, 0.f };
	pObj->Transform()->SetOffset(Offset);
}

void CManaProgrssUIScript::SaveToFile(ofstream& _File)
{
	CUIScript::SaveToFile(_File);
}

void CManaProgrssUIScript::LoadFromFile(ifstream& _File)
{
	CUIScript::LoadFromFile(_File);
}
