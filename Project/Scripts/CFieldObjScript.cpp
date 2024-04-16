#include "pch.h"
#include "CFieldObjScript.h"

#include <Engine/CAnim.h>

#include "AirSlash.h"
#include "CDeck.h"
#include "CFieldScript.h"
#include "CMagic.h"

#include "CProjectileScript.h"
#include "CPlayerCursorScript.h"
#include "FrostBoltMagic.h"
#include "Terraform.h"
#include "CDiagBeam.h"
#include "CPurpleDisc.h"
#include "Spine.h"

CFieldObjScript::CFieldObjScript()
	: CScript((UINT)SCRIPT_TYPE::FIELDOBJSCRIPT)
	, m_status{}
	, IsPlayer(true)
	, m_Deck(nullptr)

{
	m_Deck = new CDeck;

}

CFieldObjScript::CFieldObjScript(const CFieldObjScript& _Origin)
	: CScript((UINT)SCRIPT_TYPE::FIELDOBJSCRIPT)
{
	m_Deck = new CDeck;
}

CFieldObjScript::CFieldObjScript(UINT _SCRIPTYPE)
	:CScript((UINT)_SCRIPTYPE)
{
}

CFieldObjScript::~CFieldObjScript()
{
	delete m_Deck;
}

void CFieldObjScript::tick()
{
	Shoot();
	Cast();
	FillMana();
	MovedByAttack();

	m_Deck->MoveToGrave();

	if (m_Deck->GetIsShuffle())
	{
		if (m_Deck->GetShuffleTimer() <= 0.f)
			m_Deck->FillHand();
		else
		m_Deck->GetShuffleTimer() -= DT;
	}


	//if(IsPlayer)
	//{
	//	if(KEY_TAP(KEY::R))
	//	{
	//		CGameObject* Diag = CPrefab::GetPrefabObj(PrefabPurpleDisc);

	//		Vec2 SpawnRowCol = { 5, 3 };
	//		Vec3 Position = this->GetField()->GetTilePosition(SpawnRowCol);

	//		Diag->GetScript<CPurpleDisc>()->SetStartIdx(Vec2{ 5,3 });
	//		Diag->GetScript<CPurpleDisc>()->SetShooter(this->GetOwner());
	//		Diag->GetScript<CPurpleDisc>()->SetField(this->GetField());
	//		Diag->Transform()->SetRelativePos(Position);
	//		GamePlayStatic::SpawnGameObject(Diag, LayerPlayerAttackonTile);
	//	}
	//}
}


void CFieldObjScript::UseMana(int Mana)
{
	m_status.Current_MP -= Mana;
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
			m_Deck->CastFirst();
		}

		if(KEY_TAP((KEY::W)))
		{
			m_Deck->CastSecond();
		}
	}
}

void CFieldObjScript::Hit(int Damage)
{
	Status OwnerStatus = this->GetStatus();
	OwnerStatus.Current_HP -= Damage;

	SetStatus(OwnerStatus);

	b_Heat = true;
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

void CFieldObjScript::MovedByAttack()
{
	if(b_Moved)
	{
		Vec2 Idx = this->GetOwnerIdx() + MovedIdxDir;

		Vec3 MoveTilePos = m_Field->GetTilePosition(Idx);

		Vec3 Direction = MoveTilePos - this->Transform()->GetRelativePos();
		float Distance = Direction.Length();

		Direction.Normalize();

		Vec3 NewPos = this->Transform()->GetRelativePos();
		NewPos += Direction * 600.f * DT;

		this->Transform()->SetRelativePos(NewPos);

		float xpos = MoveTilePos.x - NewPos.x;
		float ypos = MoveTilePos.y - NewPos.y;

		if(xpos < 1.f && ypos < 1.f)
		{
			MoveTilePos.z -= 50.f;
			this->Transform()->SetRelativePos(MoveTilePos);
			this->SetOwnerIdx(Idx);
			b_Moved = false;
			MovedIdxDir = Vec2{ 0, 0 };

		}

	}
}

void CFieldObjScript::begin()
{
	if(IsPlayer)
	{
		Status PlayerState = this->GetStatus();
		m_status.Owner = this->GetOwner();
		PlayerState.HP = 5000;
		PlayerState.MP = 4.f;

		PlayerState.Current_HP = PlayerState.HP;
		PlayerState.Current_MP = 0.f;

		PlayerState.Mana_Regen = 0.9;

		PlayerState.SpellPower = 0;

		PlayerState.Defense = 0;
		PlayerState.Shield = 0;

		PlayerState.Camp = 1;

		this->SetStatus(PlayerState);

		//m_Deck->AddMagic(new FrostBoltMagic);
		m_Deck->AddMagic(new FrostBoltMagic);
		m_Deck->AddMagic(new Spine);
		m_Deck->AddMagic(new AirSlash);

		m_Deck->SetOwner(this->m_Owner);
		m_Deck->begin();

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