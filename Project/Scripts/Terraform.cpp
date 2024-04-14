#include "pch.h"
#include "Terraform.h"

#include "CFieldScript.h"

#include <Engine/CAssetMgr.h>


Terraform::Terraform()
{
	m_Info.ManaCost = 2;
	m_Info.SpellName = "Terraforming";
	m_Info.m_keyWard = KeyWard::Boss;
	m_Info.m_Type = MagicType::Ground;
	m_Info.Dmg = 50;
	m_Info.TotalHit = 1;

	m_Info.StartIdx = Vec2{ -4, 0 };

	m_Info.CastRange[6][4] = true;
	m_Info.CastRange[6][7] = true;
	m_Info.CastRange[3][4] = true;
	m_Info.CastRange[3][7] = true;


	MagicIcon = CPrefab::GetPrefabObj(PrefabTerraicon);
	MagicIcon->Transform()->SetRelativePos(SpellGravesPos);
	GamePlayStatic::SpawnGameObject(MagicIcon, LayerDefault);
}

Terraform::~Terraform()
{
}

void Terraform::cast(Vec2 StartPoint)
{
	// StartPoint is no ghost tile and use position to magic
	if (Caster->GetScript<CFieldObjScript>()->GetStatus().Camp == 1)
		StartPoint = Vec2{7 , 0 };
	else if (Caster->GetScript<CFieldObjScript>()->GetStatus().Camp == 2)
		StartPoint = Vec2{ 3 , 0 };

	for (int row = 0; row < TileMaxRow; ++row)
	{
		for (int col = 0; col < TileMaxCol - 8; ++col)
		{
			int castrow = 3 - StartPoint.y + row;
			int castcol = 7 - StartPoint.x + col;
			if (m_Info.CastRange[castrow][castcol] == true)
			{
				Vec2 SpawnRow = { (float)col, (float)row }; // must col row  
				TerraBeam = CPrefab::GetPrefabObj(PrefabTerraBeam);
				SetField(Caster->GetScript<CFieldObjScript>()->GetField());
				Vec3 Position = CurField->GetTilePositionToMagic(SpawnRow);
				Position.z = 0.f;


				TerraBeam->Transform()->SetOffset(Vec2{ 0.f, 515.f });
				TerraBeam->Transform()->SetRelativePos(Position);


				GamePlayStatic::SpawnGameObject(TerraBeam, LayerMonsterAttack);
				
				TerraBeam->Animator2D()->Play(L"TerraBeam", false);

			}

		}
	}
}
