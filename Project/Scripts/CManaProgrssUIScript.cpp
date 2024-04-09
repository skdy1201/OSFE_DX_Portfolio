#include "pch.h"
#include "CManaProgrssUIScript.h"

CManaProgrssUIScript::CManaProgrssUIScript()
	: ManaRegen(0.5)
{
}

CManaProgrssUIScript::~CManaProgrssUIScript()
{
}

void CManaProgrssUIScript::begin()
{
	CUIScript::begin();
}

void CManaProgrssUIScript::tick()
{
	Vec3 Scale = pObj->Transform()->GetRelativeScale();
	Scale.x += (DT * ManaRegen) * ManaProgrssScaleX;
	pObj->Transform()->SetRelativeScale(Scale);

	float offsetx =  Scale.x/2;
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
