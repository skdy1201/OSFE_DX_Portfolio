#include "pch.h"
#include "AirSlash.h"

#include "CFieldScript.h"
#include "CFieldObjScript.h"
#include "CWideShot.h"

AirSlash::AirSlash()
{
	m_Info.ManaCost = 1;
	m_Info.SpellName = "Air Slash";
	m_Info.m_keyWard = KeyWard::Anima;
	m_Info.m_Type = MagicType::Shot;
	m_Info.Dmg = 10;
	m_Info.TotalHit = 1;

	m_Info.StartIdx = Vec2{ -4, 0 };

	m_Info.CastRange[3][7] = true;


	pWideShot = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\WideShot.pref", L"prefab\\WideShot.pref");

	MagicIcon = CPrefab::GetPrefabObj(L"prefab\\AirSlashDeckIcon.pref");
	MagicIcon->Transform()->SetRelativePos(SpellGravesPos);
	GamePlayStatic::SpawnGameObject(MagicIcon, LayerUI);
}

AirSlash::~AirSlash()
{
}

void AirSlash::cast(Vec2 StartPoint)
{
	StartPoint += m_Info.StartIdx;

	for (int row = 0; row < TileMaxRow; ++row)
	{
		for (int col = 0; col < TileMaxCol - 8; ++col)
		{
			int castrow = 3 - StartPoint.y + row;
			int castcol = 7 - StartPoint.x + col;
			if (m_Info.CastRange[castrow][castcol] == true)
			{
				CGameObject* slash = pWideShot->Instantiate();
				Vec2 SpawnRowCol = { col + 4, row };

				SetField(Caster->GetScript<CFieldObjScript>()->GetField());
				Vec3 Position = CurField->GetTilePosition(SpawnRowCol);
				Position.z = ProjectileZ;

				slash->GetScript<CWideShot>()->SetStartIdx(SpawnRowCol);
				slash->GetScript<CWideShot>()->SetDir(Vec3(1.f, 0.f, 0.f));
				slash->GetScript<CWideShot>()->SetShooter(Caster);
				slash->GetScript<CWideShot>()->SetField(this->GetField());
				slash->Transform()->SetRelativePos(Position);

				slash->Transform()->SetOffset(Vec2{ 0.f, 40.f });

				GamePlayStatic::SpawnGameObject(slash, LayerPlayerAttack, 0.f);
				GamePlayStatic::Play2DSound(L"sound\\sword_laser.wav", 1, 0.5f);


			}

		}
	}
}
