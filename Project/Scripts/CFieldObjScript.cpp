#include "pch.h"
#include "CFieldObjScript.h"
#include "CFieldScript.h"



CFieldObjScript::CFieldObjScript()
	: CScript(FIELDOBJSCRIPT)
	, m_Health{}
	, IsPlayer(true)

{
}

CFieldObjScript::CFieldObjScript(const CFieldObjScript& _Origin)
	: CScript(FIELDOBJSCRIPT)
{
}

CFieldObjScript::~CFieldObjScript()
{
}

void CFieldObjScript::Move()
{
	if(IsPlayer == true)
	{
		if(KEY_TAP(KEY::W))
		{
			Vec2 Index = GetOwnerIdx();

			Vec2 NextIndex = { Index.x, Index.y + 1 };

			if (NextIndex.y >= TileMaxRow)
				return;

			m_Field->MoveToTile(m_Owner, NextIndex);
			SetOwnerIdx(NextIndex);


		}

		if (KEY_TAP(KEY::S))
		{
			Vec2 Index = GetOwnerIdx();

			Vec2 NextIndex = { Index.x, Index.y - 1 };

			if (NextIndex.y < 0)
				return;
				
			m_Field->MoveToTile(m_Owner, NextIndex);
			SetOwnerIdx(NextIndex);
		}

			if (KEY_TAP(KEY::A))
			{
				Vec2 Index = GetOwnerIdx();

				Vec2 NextIndex = { Index.x - 1, Index.y };

				m_Field->MoveToTile(m_Owner, NextIndex);
				SetOwnerIdx(NextIndex);
			}

			if (KEY_TAP(KEY::D))
			{
				Vec2 Index = GetOwnerIdx();

				Vec2 NextIndex = { Index.x + 1, Index.y};

				m_Field->MoveToTile(m_Owner, NextIndex);
				SetOwnerIdx(NextIndex);
			}
	}
}

void CFieldObjScript::begin()
{
}

void CFieldObjScript::tick()
{
	Move();
}

void CFieldObjScript::SaveToFile(ofstream& _File)
{
}

void CFieldObjScript::LoadFromFile(ifstream& _File)
{
}
