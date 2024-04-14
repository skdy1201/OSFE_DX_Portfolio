#include "pch.h"
#include "BossDiscMagic.h"

#include "CFieldScript.h"
#include "CPurpleDisc.h"

BossDiscMagic::BossDiscMagic()
{
	m_Info.ManaCost = 0;
	m_Info.SpellName = "PurpleDisc";
	m_Info.m_keyWard = KeyWard::Boss;
	m_Info.m_Type = MagicType::Shot;
	m_Info.Dmg = 50;
	m_Info.TotalHit = 1;

	PurpleDiscProj = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\PurpleDisc.pref", L"prefab\\PurpleDisc.pref");
}

BossDiscMagic::~BossDiscMagic()
{
}

void BossDiscMagic::cast(Vec2 StartPoint)
{
	CGameObject* disc = PurpleDiscProj->Instantiate();
	disc->GetScript<CPurpleDisc>()->SetShooter(Caster);
	disc->GetScript<CPurpleDisc>()->SetField(this->GetField());
	disc->GetScript<CPurpleDisc>()->SetStartIdx(StartPoint);

	CFieldScript* field = this->GetField();
	Vec3 Pos = field->GetTilePosition(StartPoint);

	disc->Transform()->SetRelativePos(Pos);

	GamePlayStatic::SpawnGameObject(disc, LayerMonsterAttackonTile, 0);
}
