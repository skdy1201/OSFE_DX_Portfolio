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
	m_status.Current_MP = 0.f;
	m_status.Owner = this->GetOwner();
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
	FillMana();
	
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
		Status PlayerState = this->GetStatus();
		PlayerState.HP = 500;
		PlayerState.MP = 4.f;

		PlayerState.Current_MP = PlayerState.HP;
		PlayerState.Current_MP = 0.f;

		PlayerState.Mana_Regen = 0.3;

		PlayerState.SpellPower = 0;

		PlayerState.Defense = 0;
		PlayerState.Shield = 0;

		PlayerState.Camp = 1;

		this->SetStatus(PlayerState);


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

	this->GetOwner()->GetRenderComopnent()->SetMaterial(this->GetRenderComponent()->GetDynamicMaterial());
}

void CFieldObjScript::FillMana()
{
	if (m_Owner == nullptr)
		return;

	m_status.Current_MP += DT * m_status.Mana_Regen;

	if(m_status.Current_MP >= m_status.MP)
	{
		m_status.Current_MP = m_status.MP;
	}

	if (m_status.Current_MP < 0.f)
	{
		m_status.Current_MP = 0;
	}
}


void CFieldObjScript::SaveToFile(ofstream& _File)
{
}

void CFieldObjScript::LoadFromFile(ifstream& _File)
{
}