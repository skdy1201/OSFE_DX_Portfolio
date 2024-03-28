#include "pch.h"
#include "CFieldScript.h"

#include <Engine/components.h>
#include "CTileScript.h"

CFieldScript::CFieldScript()
	:CScript(FIELDSCRIPT)
{
}

CFieldScript::CFieldScript(const CFieldScript& _Origin)
	: CScript(FIELDSCRIPT)
	, TileRow(_Origin.TileRow)
	, TileCol(_Origin.TileCol)
{

}


CFieldScript::~CFieldScript()
{
}

void CFieldScript::SaveToFile(ofstream& _File)
{
	_File << TileRow << " " << TileCol << endl;
}

void CFieldScript::LoadFromFile(ifstream& _File)
{
	_File >> TileRow >> TileCol;
}



void CFieldScript::begin()
{
	SpawnTile(TileRow, TileCol);

}

void CFieldScript::tick()
{

}

void CFieldScript::SpawnTile(int Row, int Col)
{
	Ptr<CPrefab> Bprefab = CAssetMgr::GetInst()->Load<CPrefab>(BTILEPrefabKey, BTILEPrefabKey);
	Ptr<CPrefab> Rprefab = CAssetMgr::GetInst()->Load<CPrefab>(RTILEPrefabKey, RTILEPrefabKey);
	CGameObject* GameObj;

	for (int i = 0; i < TileMaxRow; ++i)
	{
		for (int j = 0; j < TileMaxCol; ++j)
		{
			if(j < 8)
			{
				GameObj = Bprefab->Instantiate();
			}
			else
			{
				GameObj = Rprefab->Instantiate();

			}
			
			CTileScript* pScript = GameObj->GetScript<CTileScript>();
			pScript ->SetTilePosition(i, j);
			GamePlayStatic::SpawnGameObject(GameObj, 0);
			this->GetOwner()->AddChild(GameObj);

			

			Vec2 idx = { i , j };
			pair<CGameObject*, Vec2> temp = make_pair(GameObj, idx);
			TileRegistry.push_back(temp);

			if (j < 4 || j > 11)
			{
				GameObj->MeshRender()->SetRenderPossible(false);
			}

			
		}
	}

	int d = 0;
	
}