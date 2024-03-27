#include "pch.h"
#include "CTileInfoScript.h"

#include <Engine/CGameObject.h>
#include <Engine/CAssetMgr.h>


CTileInfoScript::CTileInfoScript()
	: CScript(TILEINFOSCRIPT)
	, Camp(0)
	, RowCol(0, 0)
	, CurState(0)
	, IsVisible(false)
	, TileChild{}
{
}

CTileInfoScript::CTileInfoScript(const CTileInfoScript& _Origin)
	: CScript(TILEINFOSCRIPT),
	  Camp(_Origin.Camp),
	  RowCol(_Origin.RowCol),
	  CurState(_Origin.CurState),
	  IsVisible(_Origin.IsVisible),
	  TileChild{nullptr}
{
	for (int i = 0; i < (int)TileChild::End; ++i)
	{
		if(_Origin.TileChild[i] != nullptr)
		TileChild[i] = _Origin.TileChild[i]->Clone();

	}
}

CTileInfoScript::~CTileInfoScript()
{
	
}


void CTileInfoScript::begin()
{
	SpawnTile();
}

void CTileInfoScript::tick()
{

}

void CTileInfoScript::SaveToFile(ofstream& _File)
{
	_File << Camp << endl;
	_File << RowCol.first << RowCol.second << endl;
	_File << CurState << endl;

}

void CTileInfoScript::LoadFromFile(ifstream& _File)
{
	_File >> Camp;
	_File >> RowCol.first >> RowCol.second;
	_File >> CurState;
	_File >> IsVisible;
}

void CTileInfoScript::SpawnTile()
{
	CGameObject* TempObject = nullptr;
	Ptr<CPrefab> TempPrefab = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\InTile.pref", L"prefab\\InTile.pref");

	// 타일 내부
	TempObject = TempPrefab->Instantiate();
	GamePlayStatic::SpawnGameObject(TempObject, 0);
	this->GetOwner()->AddChild(TempObject);

	TileChild[0] = TempObject;


	TempPrefab = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\TileBreak.pref", L"prefab\\TileBreak.pref");

	// 깨진 타일 이미지
	TempObject = TempPrefab->Instantiate();
	GamePlayStatic::SpawnGameObject(TempObject, 0);
	this->GetOwner()->AddChild(TempObject);

	TileChild[1] = TempObject;


	TempPrefab = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\TileShadow.pref", L"prefab\\TileShadow.pref");

	// 타일 그림자
	TempObject = TempPrefab->Instantiate();
	GamePlayStatic::SpawnGameObject(TempObject, 0);
	this->GetOwner()->AddChild(TempObject);

	TileChild[2] = TempObject;

	// 에니메이터
	TempObject = new CGameObject;
	TempObject->SetName(L"TILE Animator");
	TempObject->AddComponent(new CTransform);
	TempObject->AddComponent(new CAnimator2D);

	GamePlayStatic::SpawnGameObject(TempObject, 0);
	this->GetOwner()->AddChild(TempObject);


	TileChild[3] = TempObject;



}

