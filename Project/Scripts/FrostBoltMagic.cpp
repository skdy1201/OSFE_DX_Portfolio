#include "pch.h"
#include "FrostBoltMagic.h"

#include "CFieldScript.h"
#include "CFrostBolt.h"
FrostBoltMagic::FrostBoltMagic()
	
{
	m_Info.ManaCost = 2;
	m_Info.SpellName = "Forst Blast";
	m_Info.m_keyWard = KeyWard::Anima;
	m_Info.m_Type = MagicType::Shot;
	m_Info.Dmg = 50;
	m_Info.TotalHit = 1;
	
	m_Info.CastRange[3][7] = true;

	FrostBolt = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\FrostBolt.pref", L"prefab\\FrostBolt.pref");
}

FrostBoltMagic::~FrostBoltMagic()
{
}

void FrostBoltMagic::cast(Vec2 StartPoint)
{
	for (int row = 0; row < TileMaxRow; ++row)
	{
		for (int col = 0; col < TileMaxCol - 8; ++col)
		{
			int castrow = 3 - StartPoint.y + row;
			int castcol = 7 - StartPoint.x + col;
			if (m_Info.CastRange[castrow][castcol] == true)
			{
				CGameObject* bolt = FrostBolt->Instantiate();
				Vec2 SpawnRowCol = { col+4, row };

				SetField(Caster->GetScript<CFieldObjScript>()->GetField());
				Vec3 Position = CurField->GetTilePosition( SpawnRowCol );
				Position.z = ProjectileZ;

				bolt->GetScript<CFrostBolt>()->SetStartIdx(SpawnRowCol);
				bolt->GetScript<CFrostBolt>()->SetTargetDir(Vec2(SpawnRowCol.y,SpawnRowCol.x + 1 ));
				bolt->GetScript<CFrostBolt>()->SetShooter(Caster);
				bolt->GetScript<CFrostBolt>()->SetField(this->GetField());
				bolt->Transform()->SetRelativePos(Position);

			
				GamePlayStatic::SpawnGameObject(bolt, 0);


			}

		}
	}
}
