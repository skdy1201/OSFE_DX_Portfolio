#pragma once

#include <Engine/CScript.h>
#include <Engine/components.h>


class CFieldScript :
    public CScript
{
public:
	int TileRow;
	int TileCol;

	vector<pair<CGameObject*, Vec2>> TileRegistry;
	

public:
	void SpawnTile(int Row, int Col);

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

