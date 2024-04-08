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
	Shoot();
	Cast();

}


void CFieldObjScript::Shoot()
{
}	

void CFieldObjScript::Cast()
{
	if(IsPlayer == true)
	{
		if (KEY_TAP(KEY::Q))
		{
			FrostBoltMagic* bolt = new FrostBoltMagic;
			bolt->SetCaster(this->m_Owner);
			Vec2 StartPoint = this->GetOwnerIdx();
			bolt->cast(StartPoint - Vec2{ 4, 0 });

		}
	}
}

void CFieldObjScript::Hit(int Damage)
{
	Status OwnerStatus = GetStatus();
	OwnerStatus.Current_HP -= Damage;

	SetStatus(OwnerStatus);

}

void CFieldObjScript::GetBuff()
{
}

Vec2 CFieldObjScript::GetMoveIdx(Vec2 TargetDirIdx)
{
	Vec2 Index = GetOwnerIdx();

	Vec2 NextIndex = { Index.x + TargetDirIdx.x, Index.y + TargetDirIdx.y };

	if (NextIndex.y >= TileMaxRow)
		NextIndex.y = 3;

	if (NextIndex.x <= 3)
		NextIndex.x = 3;

	return NextIndex;
}

void CFieldObjScript::begin()
{
	if(IsPlayer)
	{
		CGameObject* Cursor;
		Ptr<CPrefab> Cursorprefab = CAssetMgr::GetInst()->Load<CPrefab>(PrefabPlayerCursor, PrefabPlayerCursor);
		Cursor = Cursorprefab->Instantiate();

		CPlayerCursorScript* pScript = Cursor->GetScript<CPlayerCursorScript>();
		pScript->SetField(m_Field);
		pScript->SetPlayerScript(this);
		pScript->SetIndex((this->GetOwnerIdx() + PlayerAttackRange));

		GamePlayStatic::SpawnGameObject(Cursor, 0);
		m_Owner->AddChild(Cursor);

		if(StateMachine())
		{
			StateMachine()->AddBlackboardData(L"Player", BB_DATA::OBJECT, m_Owner);
			StateMachine()->AddBlackboardData(L"NextIdx", BB_DATA::VEC2, &NextIdx);
			StateMachine()->GetFSM()->ChangeState(L"CPlayerEntryState");
		}
	}
}

void CFieldObjScript::SaveToFile(ofstream& _File)
{
}

void CFieldObjScript::LoadFromFile(ifstream& _File)
{
}
