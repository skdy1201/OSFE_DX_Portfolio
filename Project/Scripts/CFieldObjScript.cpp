#include "pch.h"
#include "CFieldObjScript.h"
#include "CFieldScript.h"

#include "CProjectileScript.h"
#include "CPlayerCursorScript.h"


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
		if(KEY_TAP(KEY::UP))
		{
			Vec2 Index = GetOwnerIdx();

			Vec2 NextIndex = { Index.x, Index.y + 1 };

			if (NextIndex.y >= TileMaxRow)
				return;

			m_Field->MoveToTile(m_Owner, NextIndex, PlayerZ);


		}

		if (KEY_TAP(KEY::DOWN))
		{
			Vec2 Index = GetOwnerIdx();

			Vec2 NextIndex = { Index.x, Index.y - 1 };

			if (NextIndex.y < 0)
				return;
				
			m_Field->MoveToTile(m_Owner, NextIndex, PlayerZ);

		}

			if (KEY_TAP(KEY::LEFT))
			{
				Vec2 Index = GetOwnerIdx();

				Vec2 NextIndex = { Index.x - 1, Index.y };

				m_Field->MoveToTile(m_Owner, NextIndex, PlayerZ);

			}

			if (KEY_TAP(KEY::RIGHT))
			{
				Vec2 Index = GetOwnerIdx();

				Vec2 NextIndex = { Index.x + 1, Index.y};

				m_Field->MoveToTile(m_Owner, NextIndex, PlayerZ);

			}

	}
}

void CFieldObjScript::Shoot()
{
	if (KEY_TAP(KEY::E))
	{
		CGameObject* GameObj;
		Ptr<CPrefab> prefab = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\PlayerBullet.pref", L"prefab\\PlayerBullet.pref");
		GameObj = prefab->Instantiate();

		CProjectileScript* pProjScript = GameObj->GetScript<CProjectileScript>();

		Proj_Struct info = pProjScript->GetInfo();

		pProjScript->Shoot(this->GetOwner(), this->m_Field, info);

		GamePlayStatic::SpawnGameObject(GameObj, 0);
	}
}



void CFieldObjScript::begin()
{
	if(IsPlayer)
	{
		CGameObject* Cursor;
		Ptr<CPrefab> Cursorprefab = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\PlayerCursor.pref", L"prefab\\PlayerCursor.pref");
		Cursor = Cursorprefab->Instantiate();

		CPlayerCursorScript* pScript = Cursor->GetScript<CPlayerCursorScript>();
		pScript->SetField(m_Field);
		pScript->SetPlayerScript(this);
		pScript->SetIndex((this->GetOwnerIdx() + PlayerAttackRange));

		GamePlayStatic::SpawnGameObject(Cursor, 0);
		m_Owner->AddChild(Cursor);
		

	}
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
