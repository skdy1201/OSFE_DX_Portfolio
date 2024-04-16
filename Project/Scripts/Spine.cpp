#include "pch.h"
#include "Spine.h"


#include "CFieldScript.h"

#include <Engine/CAssetMgr.h>

Spine::Spine()
{
	m_Info.ManaCost = 1;
	m_Info.SpellName = "Spine";
	m_Info.m_keyWard = KeyWard::Anima;
	m_Info.m_Type = MagicType::Ground;
	m_Info.Dmg = 15;
	m_Info.TotalHit = 1;

	m_Info.StartIdx = Vec2{ 0, 0 };

	m_Info.CastRange[3][7] = true;
	m_Info.CastRange[2][7] = true;
	m_Info.CastRange[4][7] = true;
	m_Info.CastRange[3][8] = true;
	m_Info.CastRange[3][6] = true;


	MagicIcon = CPrefab::GetPrefabObj(L"prefab\\SpineMagicIcon.pref");
	MagicIcon->Transform()->SetRelativePos(SpellGravesPos);
	GamePlayStatic::SpawnGameObject(MagicIcon, LayerUI);

}

Spine::~Spine()
{
}

void Spine::cast(Vec2 StartPoint)
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
				Vec2 SpawnRow = { (float)col, (float)row }; // must col row  
				pSpine = CPrefab::GetPrefabObj(L"prefab\\Spine.pref");
				SetField(Caster->GetScript<CFieldObjScript>()->GetField());
				Vec3 Position = CurField->GetTilePositionToMagic(SpawnRow);
				Position.z = 0.f;


				pSpine->Transform()->SetOffset(Vec2{ 0.f, 0.f });
				pSpine->Transform()->SetRelativePos(Position);


				GamePlayStatic::SpawnGameObject(pSpine, LayerPlayerAttack);

				GamePlayStatic::Play2DSound(L"sound\\fast_simple_chop.wav", 1, 0.7);

				pSpine->Animator2D()->Play(L"Spine", true);

			}

		}

		
	}
}
