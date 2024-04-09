#include "pch.h"
#include "CUIScript.h"

CUIScript::CUIScript()
	: CScript((UINT)SCRIPT_TYPE::UISCRIPT)
{
}

CUIScript::CUIScript(UINT _int)
	: CScript(_int)
{
}

CUIScript::~CUIScript()
{
}

void CUIScript::begin()
{
	pObj = GetOwner();
}

void CUIScript::tick()
{
	Vec3 Scale = pObj->Transform()->GetRelativeScale();
	Scale.x += DT* 50;
	pObj->Transform()->SetRelativeScale(Scale);

	Vec3 Transform = pObj->Transform()->GetRelativePos();
	Transform.x += DT * 25;
	pObj->Transform()->SetRelativePos(Transform);
}

void CUIScript::SaveToFile(ofstream& _File)
{
}

void CUIScript::LoadFromFile(ifstream& _File)
{
}
