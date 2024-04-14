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
	SpawnFieldObj(Vec2{ 5, 2 }, PrefabPlayer,LayerPlayer, true);
	SpawnFieldObj(Vec2{8 , 2 }, PrefabSniper, LayerMonster, false);
	SpawnFieldObj(Vec2{10 , 0 }, PrefabTerra, LayerMonster, false);



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

			GamePlayStatic::SpawnGameObject(GameObj, LayerTile);

			this->GetOwner()->AddChild(GameObj);
			TileRegistry[i][j] = GameObj;

			if (j < 4 || j > 11)
			{
				GameObj->MeshRender()->SetRenderPossible(false);
			}
		}
	}
}

void CFieldScript::SpawnFieldObj(Vec2 TileIndex, wstring _prefabkey, int Layernum, bool IsPlayer)
{
	//프리팹 받아두기
	CGameObject* GameObj = nullptr;
	GameObj = CPrefab::GetPrefabObj(_prefabkey);

	// 위치 선정
	SetObjPosinTile(TileIndex, GameObj);

	// Obj의 Script를 받아둔다.
	CFieldObjScript* pScript = GameObj->GetScript<CFieldObjScript>();
	pScript->SetOwnerIdx(Vec2(TileIndex.x, TileIndex.y));
	pScript->SetPlayer(IsPlayer);
	pScript->SetOwner(GameObj);
	pScript->SetField(this);

	if(IsPlayer)
	{
		GameObj->SetName(L"Player");
		Player = GameObj;
	}
	//외부 설정(Field 내에서 해당 obj에 해야 하는 일
	SetFObjAboutField(GameObj);

	GamePlayStatic::SpawnGameObject(GameObj, Layernum);
}

void CFieldScript::SetObjPosinTile(Vec2 TileIndex, CGameObject* Obj)
{
	Vec3 SpawnPosition;
	SpawnPosition = TileRegistry[TileIndex.y][TileIndex.x]->Transform()->GetRelativePos();
	SpawnPosition.z = PlayerZ;
	Obj->Transform()->SetRelativePos(SpawnPosition);

}

void CFieldScript::SetFObjAboutField(CGameObject* Object)
{
	this->GetOwner()->AddChild(Object);
	CurFieldMember.push_back(Object);
}

//Fieldobj 전용 함수로 이름 변경예정
Vec3 CFieldScript::GetNextTilePos(CGameObject* _Owner, Vec2 _Index, float _PositionZ)
{
	Vec3 Position = GetTilePosition(_Index);
	Position.z = _PositionZ;

	CFieldObjScript* pScript = _Owner->GetScript<CFieldObjScript>();
	pScript->SetOwnerIdx(_Index);

	return Position;
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

Vec3 CFieldScript::GetTilePositionToMagic(Vec2& _TileIdx)
{
	Vec3 Position = {};

	if (_TileIdx.y < 4 && _TileIdx.y >= 0)
		Position = TileRegistry[_TileIdx.y][_TileIdx.x+4]->Transform()->GetRelativePos();
	else if (_TileIdx.y >= TileMaxRow)
	{
		Position = TileRegistry[TileMaxRow - 1][_TileIdx.x+4]->Transform()->GetRelativePos();
		Position.y += (TileY + Tilespacey);
		_TileIdx.y = TileMaxRow - 1;
	}
	else if (_TileIdx.y < 0)
	{
		Position = TileRegistry[0][_TileIdx.x+4]->Transform()->GetRelativePos();
		Position.y -= (TileY + Tilespacey);
		_TileIdx.y = 0;
	}

	return Position;
}
