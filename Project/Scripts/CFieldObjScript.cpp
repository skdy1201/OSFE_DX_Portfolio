#include "pch.h"
#include "CFieldObjScript.h"

#include <Engine/CAnim.h>

#include "CFieldScript.h"
#include "CMagic.h"

#include "CProjectileScript.h"
#include "CPlayerCursorScript.h"
#include "FrostBoltMagic.h"

CFieldObjScript::CFieldObjScript()
	: CScript((UINT)SCRIPT_TYPE::FIELDOBJSCRIPT)
	, m_status{}
	, IsPlayer(true)
	, temp(0)

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
	
	if(IsPlayer && m_Owner->Animator2D()->GetCurAnim()->GetName() == wstring(L"SaffronSpawn")
		&& m_Owner->Animator2D()->GetCurAnim()->IsFinish())
	{
		StateMachine()->GetFSM()->ChangeState(L"CPlayerIdleState");
		
	}
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

			m_Owner->Animator2D()->Play(L"SaffronMoveUp" , false);

		}

		if (KEY_TAP(KEY::DOWN))
		{
			Vec2 Index = GetOwnerIdx();

			Vec2 NextIndex = { Index.x, Index.y - 1 };

			if (NextIndex.y < 0)
				return;
				
			m_Field->MoveToTile(m_Owner, NextIndex, PlayerZ);

			m_Owner->Animator2D()->Play(L"SaffronMoveDown", false);

		}

			if (KEY_TAP(KEY::LEFT))
			{
				Vec2 Index = GetOwnerIdx();

				Vec2 NextIndex = { Index.x - 1, Index.y };

				m_Field->MoveToTile(m_Owner, NextIndex, PlayerZ);

				m_Owner->Animator2D()->Play(L"SaffronMoveBack", false);

			}

			if (KEY_TAP(KEY::RIGHT))
			{
				Vec2 Index = GetOwnerIdx();

				Vec2 NextIndex = { Index.x + 1, Index.y};

				m_Field->MoveToTile(m_Owner, NextIndex, PlayerZ);

				m_Owner->Animator2D()->Play(L"SaffronMoveFront", false);

			}


			if(KEY_TAP(KEY::Q))
			{
				FrostBoltMagic* bolt = new FrostBoltMagic;
				bolt->SetCaster(this->m_Owner);
				Vec2 StartPoint = this->GetOwnerIdx();
				bolt->cast(StartPoint - Vec2{4, 0});

			}
	}
}

void CFieldObjScript::Shoot()
{
	if (IsPlayer)
	{
		if (KEY_TAP(KEY::E))
		{
			CGameObject* GameObj;
			GameObj = CPrefab::GetPrefabObj(L"prefab\\PlayerBullet.pref");

			CProjectileScript* pProjScript = GameObj->GetScript<CProjectileScript>();
			Proj_Struct info = pProjScript->GetInfo();

			pProjScript->Shoot(this->GetOwner(), this->m_Field, Vec2(10.f, 0.f), info);
			pProjScript->SetDir(Vec3(1.f, 0.f, 0.f));

			GamePlayStatic::SpawnGameObject(GameObj, 0);

		}

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
		
		m_Owner->Animator2D()->Play(L"SaffronSpawn", false);

		if(StateMachine())
		{
			StateMachine()->AddBlackboardData(L"Player", BB_DATA::OBJECT, m_Owner);

		}

	}
}

void CFieldObjScript::SaveToFile(ofstream& _File)
{
}

void CFieldObjScript::LoadFromFile(ifstream& _File)
{
}
