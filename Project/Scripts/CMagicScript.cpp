#include "pch.h"
#include "CMagicScript.h"

#include "CFieldScript.h"
#include "CFieldObjScript.h"

CMagicScript::CMagicScript()
	: CScript((UINT)SCRIPT_TYPE::MAGICSCRIPT)
	, m_MagicInfo()
	, MagicField()
{
	MagicField.resize(8);
	for(int i = 0; i < 8; ++i)
	{
		MagicField[i].resize(16);

		for(int j = 0; j < 16; ++j)
		{
			MagicField[i][j] = false;
		}
	}

}

CMagicScript::CMagicScript(const CMagicScript& _Origin)
	: CScript((UINT)SCRIPT_TYPE::MAGICSCRIPT)
	, m_MagicInfo(_Origin.m_MagicInfo)
	, MagicField(_Origin.MagicField)
{

}

CMagicScript::~CMagicScript()
{
	
}

void CMagicScript::SetMagicField()
{
	for(int i = 0; i < m_MagicInfo.CastRange.size(); ++i)
	{
		Vec2 TileIdx = m_MagicInfo.CastRange[i];

		MagicField[TileIdx.x][TileIdx.y] = true;
	}
}

vector<vector<bool>>& CMagicScript::CalculateRange(Vec2 _StartIdx)
{
	vector<vector<bool>> temp;
	return temp;
}

void CMagicScript::begin()
{
	SetMagicField();
}

void CMagicScript::tick()
{
}

void CMagicScript::SaveToFile(ofstream& _File)
{
}

void CMagicScript::LoadFromFile(ifstream& _File)
{
}
