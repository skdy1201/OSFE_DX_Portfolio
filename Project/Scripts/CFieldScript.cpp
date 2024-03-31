#include "pch.h"
#include "CFieldScript.h"

#include <Engine/components.h>
#include "CTileScript.h"
#include "CFieldObjScript.h"

CFieldScript::CFieldScript()
	:CScript((UINT)SCRIPT_TYPE::FIELDSCRIPT)
{
	MaxTileRow = TileMaxRow;
	MaxTileCol = TileMaxCol;
}

CFieldScript::CFieldScript(const CFieldScript& _Origin)
	: CScript((UINT)SCRIPT_TYPE::FIELDSCRIPT)
	, MaxTileRow(_Origin.MaxTileRow)
	, MaxTileCol(_Origin.MaxTileCol)
{


}


CFieldScript::~CFieldScript()
{
}

void CFieldScript::SaveToFile(ofstream& _File)
{
	_File << MaxTileRow << " " << MaxTileCol << endl;
}

void CFieldScript::LoadFromFile(ifstream& _File)
{
	_File >> MaxTileRow >> MaxTileCol;
}



void CFieldScript::begin()
{
	SpawnTile(MaxTileRow, MaxTileCol);
	SpawnFieldObj(Vec2{ 5, 2 }, L"prefab\\temptest.pref");


}

void CFieldScript::tick()
{

}

void CFieldScript::SpawnTile(int Row, int Col)
{
	Ptr<CPrefab> Bprefab = CAssetMgr::GetInst()->Load<CPrefab>(BTILEPrefabKey, BTILEPrefabKey);
	Ptr<CPrefab> Rprefab = CAssetMgr::GetInst()->Load<CPrefab>(RTILEPrefabKey, RTILEPrefabKey);
	CGameObject* GameObj;

	TileRegistry.resize(Row);

	for (int i = 0; i < MaxTileRow; ++i)
	{
		TileRegistry[i].resize(Col);
		for (int j = 0; j < MaxTileCol; ++j)
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
			TileRegistry[i][j] = GameObj;

			if (j < 4 || j > 11)
			{
				GameObj->MeshRender()->SetRenderPossible(false);
			}
		}
	}
}

void CFieldScript::SpawnFieldObj(Vec2 TileIndex, wstring _prefabkey)
{
	Vec3 SpawnPosition;
	Ptr<CPrefab> prefab = CAssetMgr::GetInst()->Load<CPrefab>(_prefabkey, _prefabkey);
	CGameObject* GameObj;
	GameObj = prefab->Instantiate();


	SpawnPosition = TileRegistry[TileIndex.y][TileIndex.x]->Transform()->GetRelativePos();
	SpawnPosition.z = PlayerZ;

	GameObj->Transform()->SetRelativePos(SpawnPosition);
	GamePlayStatic::SpawnGameObject(GameObj, 0);
	CFieldObjScript* pScript = GameObj->GetScript<CFieldObjScript>();
	pScript->SetOwnerIdx(Vec2(TileIndex.x, TileIndex.y));
	pScript->SetPlayer(true);
	pScript->SetOwner(GameObj);
	CurFieldMember.push_back(GameObj);
	pScript->SetField(this);


	this->GetOwner()->AddChild(GameObj);
}

//Fieldobj 전용 함수로 이름 변경예정
void CFieldScript::MoveToTile(CGameObject* _Owner, Vec2 _Index, float _PositionZ)
{
	Vec3 Position = GetTilePosition(_Index);
	Position.z = _PositionZ;
	_Owner->Transform()->SetRelativePos(Position);

	CFieldObjScript* pScript = _Owner->GetScript<CFieldObjScript>();
	pScript->SetOwnerIdx(_Index);
}

Vec3 CFieldScript::GetTilePosition(Vec2& _TileIdx)
{
	Vec3 Position = {};

	if (_TileIdx.y < 4 && _TileIdx.y >= 0)
		Position = TileRegistry[_TileIdx.y][_TileIdx.x]->Transform()->GetRelativePos();
	else if (_TileIdx.y >= TileMaxRow)
	{
		Position = TileRegistry[TileMaxRow - 1][_TileIdx.x]->Transform()->GetRelativePos();
		Position.y += (TileY + Tilespacey);
		_TileIdx.y = TileMaxRow - 1;
	}
	else if (_TileIdx.y < 0)
	{
		Position = TileRegistry[0][_TileIdx.x]->Transform()->GetRelativePos();
		Position.y -= (TileY + Tilespacey);
		_TileIdx.y = 0;
	}

	return Position;

}
