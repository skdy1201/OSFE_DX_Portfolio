#include "pch.h"
#include "CMissileScript.h"


CMissileScript::CMissileScript()
	: m_fSpeed(1500.f)
	, CScript((UINT)SCRIPT_TYPE::MISSILESCRIPT)
{
}

CMissileScript::~CMissileScript()
{
}

void CMissileScript::tick()
{
	return;

	Vec3 vPos = Transform()->GetRelativePos();

	vPos.y += m_fSpeed * DT;

	Transform()->SetRelativePos(vPos);	
}

void CMissileScript::SaveToFile(ofstream& _File)
{
}

void CMissileScript::LoadFromFile(ifstream& _File)
{
}
