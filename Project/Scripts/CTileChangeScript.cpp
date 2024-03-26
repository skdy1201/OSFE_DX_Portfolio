#include "pch.h"
#include "CTileChangeScript.h"

CTileChangeScript::CTileChangeScript()
	: CScript(TILECHANGESCRIPT)
	, CurTexIdx(0)
	, PrevTexIdx(0)
	, TileMtrl(nullptr)
{
	AddScriptParam(SCRIPT_PARAM::INT, "Texture Num", &CurTexIdx);
}

CTileChangeScript::~CTileChangeScript()
{
}

void CTileChangeScript::begin()
{
	TileMtrl = GetRenderComponent()->GetDynamicMaterial();
}

void CTileChangeScript::tick()
{
	bool ischange = false;

	if (PrevTexIdx != CurTexIdx)
		ischange = true;

	if (ischange)
	{
		if (CurTexIdx == 1)
		{
			TileMtrl->SetScalarParam(SCALAR_PARAM::INT_0, 1);
		}
		else
		{
			TileMtrl->SetScalarParam(SCALAR_PARAM::INT_0, 0);
		}
	}

	PrevTexIdx = CurTexIdx;
}


void CTileChangeScript::SaveToFile(ofstream& _File)
{
}

void CTileChangeScript::LoadFromFile(ifstream& _File)
{
}
