#include "pch.h"
#include "CTileChangeScript.h"

CTileChangeScript::CTileChangeScript()
	: CScript(TILECHANGESCRIPT)
	, CurTexIdx(0)
	, TileMtrl(nullptr)
{
	AddScriptParam(SCRIPT_PARAM::INT, "Texture Num", &CurTexIdx);
}

CTileChangeScript::CTileChangeScript(const CTileChangeScript& _Origin)
	: CScript(TILECHANGESCRIPT)
	, CurTexIdx(_Origin.CurTexIdx)
	, TileMtrl(_Origin.TileMtrl)
	, Ischange(_Origin.Ischange)
	, ColorParam(_Origin.ColorParam)
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
	if (CurTexIdx == 0)
		TileMtrl->SetScalarParam(SCALAR_PARAM::INT_0, 0);
	else if (CurTexIdx == 1)
		TileMtrl->SetScalarParam(SCALAR_PARAM::INT_0, 1);
	else if (CurTexIdx == 2)
		TileMtrl->SetScalarParam(SCALAR_PARAM::INT_0, 2);

}


void CTileChangeScript::SaveToFile(ofstream& _File)
{
	_File << CurTexIdx << endl;
}

void CTileChangeScript::LoadFromFile(ifstream& _File)
{
	_File >> CurTexIdx;
}
