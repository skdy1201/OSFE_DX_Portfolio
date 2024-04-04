#include "pch.h"
#include "CFieldObjScript.h"
#include "CFieldScript.h"
#include "CMagic.h"

#include "CProjectileScript.h"
#include "CPlayerCursorScript.h"
#include "FrostBoltMagic.h"

CFieldObjScript::CFieldObjScript()
	: CScript((UINT)SCRIPT_TYPE::FIELDOBJSCRIPT)
	, m_status{}
	, IsPlayer(true)

{

}

CFieldObjScript::CFieldObjScript(const CFieldObjScript& _Origin)
	: CScript((UINT)SCRIPT_TYPE::FIELDOBJSCRIPT)
{
}

CFieldObjScript::CFieldObjScript(UINT _SCRIPTYPE)
	:CScript((UINT)_SCRIPTYPE)
{
}

CFieldObjScript::~CFieldObjScript()
{
}

void CFieldObjScript::tick()
{
	Move();
	Shoot();
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


			if(KEY_TAP(KEY::Q))
			{
				FrostBoltMagic* bolt = new FrostBoltMagic;
				bolt->SetCaster(this->m_Owner);
				Vec2 StartPoint = this->GetOwnerIdx();
				StartPoint.x  += 1;
				bolt->cast(StartPoint - Vec2{4, 0});

				StartPoint.x - 1;

				FrostBoltMagic* bolt2 = new FrostBoltMagic;
				bolt->SetCaster(this->m_Owner);
				StartPoint += Vec2{ 0, -1 };
				bolt->cast(StartPoint - Vec2{ 4, 0 });

				StartPoint.y += 1;
				StartPoint.x += -1;


				FrostBoltMagic* bolt3 = new FrostBoltMagic;
				bolt->SetCaster(this->m_Owner);
				StartPoint += Vec2{ 0, 1 };
				bolt->cast(StartPoint - Vec2{ 4, 0 });
			}
	}
}

void CFieldObjScript::Shoot()
{

	if (KEY_TAP(KEY::E))
	{
		CGameObject* GameObj;
		GameObj = CPrefab::GetPrefabObj(L"prefab\\PlayerBullet.pref");

		CProjectileScript* pProjScript = GameObj->GetScript<CProjectileScript>();
		Proj_Struct info = pProjScript->GetInfo();

		pProjScript->Shoot(this->GetOwner(), this->m_Field, info);

		GamePlayStatic::SpawnGameObject(GameObj, 0);
	}

	if (IsPlayer)
	{
		
	}
}	

void CFieldObjScript::Cast()
{
	if(IsPlayer == true)
	{
		
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

void CFieldObjScript::SaveToFile(ofstream& _File)
{
}

void CFieldObjScript::LoadFromFile(ifstream& _File)
{
}
