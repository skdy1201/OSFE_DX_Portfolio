#include "pch.h"
#include "CFieldObjScript.h"

CFieldObjScript::CFieldObjScript()
	: CScript(FIELDOBJSCRIPT)
	, m_Health{}
	, IsPlayer(false)
{
}

CFieldObjScript::CFieldObjScript(const CFieldObjScript& _Origin)
	: CScript(FIELDOBJSCRIPT)
{
}

CFieldObjScript::~CFieldObjScript()
{
}

void CFieldObjScript::begin()
{
}

void CFieldObjScript::tick()
{
}

void CFieldObjScript::SaveToFile(ofstream& _File)
{
}

void CFieldObjScript::LoadFromFile(ifstream& _File)
{
}
