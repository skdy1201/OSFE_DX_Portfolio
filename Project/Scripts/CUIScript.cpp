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

}

void CUIScript::SaveToFile(ofstream& _File)
{
}

void CUIScript::LoadFromFile(ifstream& _File)
{
}
