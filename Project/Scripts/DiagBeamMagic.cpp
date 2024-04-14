#include "pch.h"
#include "DiagBeamMagic.h"

#include "CDiagBeam.h"
#include "CFieldScript.h"

DiagBeamMagic::DiagBeamMagic()
{
	m_Info.ManaCost = 0;
	m_Info.SpellName = "DiagBeam";
	m_Info.m_keyWard = KeyWard::Boss;
	m_Info.m_Type = MagicType::Shot;
	m_Info.Dmg = 50;
	m_Info.TotalHit = 1;

	//m_Info.StartIdx = Vec2{ -4, 0 };

	//m_Info.CastRange[2][7] = true;
	//m_Info.CastRange[3][8] = true;
	//m_Info.CastRange[4][7] = true;

	DiagBeam = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\DiagBeam.pref", L"prefab\\FrostBolt.pref");

	//MagicIcon = CPrefab::GetPrefabObj(PrefabFrosticon);
	//MagicIcon->Transform()->SetRelativePos(SpellGravesPos);
	//GamePlayStatic::SpawnGameObject(MagicIcon, LayerDefault);
}

DiagBeamMagic::~DiagBeamMagic()
{


}

void DiagBeamMagic::cast(Vec2 StartPoint)
{
	CGameObject* beam = DiagBeam->Instantiate();
	beam->GetScript<CDiagBeam>()->SetShooter(Caster);
	beam->GetScript<CDiagBeam>()->SetField(this->GetField());
	beam->GetScript<CDiagBeam>()->SetStartIdx(StartPoint);

	CFieldScript* field = this->GetField();
	Vec3 Pos = field->GetTilePosition(StartPoint);

	beam->Transform()->SetRelativePos(Pos);

	GamePlayStatic::SpawnGameObject(beam, LayerMonsterAttack, 0);
	
}
