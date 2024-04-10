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

	m_Info.StartIdx = Vec2{ -4, 0 };

	m_Info.CastRange[2][7] = true;
	m_Info.CastRange[3][8] = true;
	m_Info.CastRange[4][7] = true;

	FrostBolt = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\FrostBolt.pref", L"prefab\\FrostBolt.pref");
}

FrostBoltMagic::~FrostBoltMagic()
{
}

void FrostBoltMagic::cast(Vec2 StartPoint)
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
				CGameObject* bolt = FrostBolt->Instantiate();
				Vec2 SpawnRowCol = { col+4, row };

				SetField(Caster->GetScript<CFieldObjScript>()->GetField());
				Vec3 Position = CurField->GetTilePosition( SpawnRowCol );
				Position.z = ProjectileZ;

				bolt->GetScript<CFrostBolt>()->SetStartIdx(SpawnRowCol);
				bolt->GetScript<CFrostBolt>()->SetDir(Vec3(1.f, 0.f, 0.f));
				bolt->GetScript<CFrostBolt>()->SetShooter(Caster);
				bolt->GetScript<CFrostBolt>()->SetField(this->GetField());
				bolt->Transform()->SetRelativePos(Position);

				CProjectileScript* Proj = bolt->GetScript<CProjectileScript>();
				
				if (castrow == 2 && castcol == 7)
				{
					GamePlayStatic::SpawnGameObject(bolt, LayerPlayerAttack, 0.2f);
				}else if (castrow == 3 && castcol == 8)
				{
					GamePlayStatic::SpawnGameObject(bolt, LayerPlayerAttack);

				}else
				{
					GamePlayStatic::SpawnGameObject(bolt, LayerPlayerAttack, 0.1f);
				}

			}

		}
	}
}
