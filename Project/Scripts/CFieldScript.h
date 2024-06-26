#pragma once

#include <Engine/CScript.h>
#include <Engine/components.h>
#include "CFieldObjScript.h"


class CFieldScript :
    public CScript
{
public:
	int MaxTileRow;
	int MaxTileCol;

	vector<vector<CGameObject*>> TileRegistry;
	vector<CGameObject*> CurFieldMember;
	CGameObject* Player;



public:
	//CGameObject* LinkPrefabtoObj(wstring namekey);
	void SetObjPosinTile(Vec2 TileIndex , CGameObject* Obj);
	void SetFObjAboutField(CGameObject* Object);

public:
	void SpawnTile(int Row, int Col);
	void SpawnFieldObj(Vec2 TileIndex, wstring _prefabkey, int Layernum, bool IsPlayer);

	Vec3 GetNextTilePos(CGameObject* _Owner, Vec2 _Index , float _PositionZ);

	Vec3 GetTilePosition(Vec2& _TileIdx);
	Vec3 GetTilePositionToMagic(Vec2& _TileIdx);

	void SetPlayer(CGameObject* obj) { Player = obj; }
	CGameObject* GetPlayer() { return Player; }

public:
	virtual void begin() override;
	virtual void tick() override;

	virtual void SaveToFile(ofstream& _File) override;
	virtual void LoadFromFile(ifstream& _File) override;

public:
	CLONE(CFieldScript);
	CFieldScript();
	CFieldScript(const CFieldScript& _Origin);
	~CFieldScript();
};

