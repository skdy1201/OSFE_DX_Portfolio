#include "pch.h"
#include "CBackgroundScript.h"

#include <Engine/CKeyMgr.h>

void CBackgroundScript::SaveToFile(ofstream& _File)
{
}

void CBackgroundScript::LoadFromFile(ifstream& _File)
{
}

CBackgroundScript::CBackgroundScript()
	: CScript((UINT)SCRIPT_TYPE::BACKGROUNDSCRIPT)
{
}

CBackgroundScript::~CBackgroundScript()
{
}

void CBackgroundScript::tick()
{

	static int i = 0;
	if (KEY_TAP(KEY::T))
	{
		i ? MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, 1) : MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, 0);
		i = !i;
	}
}
