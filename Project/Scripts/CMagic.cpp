#include "pch.h"
#include "CMagic.h"


#include "CFieldObjScript.h"


CMagic::CMagic()
{
	CenterPoint = Vec2(7, 3);
}

CMagic::~CMagic()
{
}

void CMagic::SetCaster(CGameObject* _Caster)
{
	Caster = _Caster;
	CurField = Caster->GetScript<CFieldObjScript>()->GetField();
}
