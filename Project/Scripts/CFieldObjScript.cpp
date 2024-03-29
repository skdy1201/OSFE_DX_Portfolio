#include "pch.h"
#include "CFieldObjScript.h"
#include "CFieldScript.h"

#include "CProjectileScript.h"


CFieldObjScript::CFieldObjScript()
	: CScript((UINT)SCRIPT_TYPE::FIELDOBJSCRIPT)
	, m_Health{}
	, IsPlayer(true)

{

}

CFieldObjScript::CFieldObjScript(const CFieldObjScript& _Origin)
	: CScript((UINT)SCRIPT_TYPE::FIELDOBJSCRIPT)
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

void CFieldObjScript::Shoot()
{
	if(KEY_TAP(KEY::E))
	{
		CGameObject* GameObj;
		//Ptr<CPrefab> prefab = CAssetMgr::GetInst()->Load<CPrefab>(_prefabkey, _prefabkey);

	}

}

void CFieldObjScript::begin()
{
}

void CFieldObjScript::tick()
{
	Move();
	Shoot();
}

void CFieldObjScript::SaveToFile(ofstream& _File)
{
}

void CFieldObjScript::LoadFromFile(ifstream& _File)
{
}
