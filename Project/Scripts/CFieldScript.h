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

public:
	void SpawnTile(int Row, int Col);
	void SpawnFieldObj(Vec2 TileIndex, wstring _prefabkey);

	void MoveToTile(CGameObject* _Owner, Vec2 _Index , float _PositionZ);

	Vec3 GetTilePosition(Vec2& _TileIdx);

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

