#pragma once

#include <Engine/CScript.h>
enum class TileState
{
	Breaking,
	Break,
	Burn,
	End,
};


class CTileScript :
	public CScript
{
private:
	int Camp;
	bool IsVisible;


	bool IsOn;
	float StateTimer[(int)TileState::End];

	Ptr<CMaterial> TileMtrl;

public:
	virtual void begin() override;
	virtual void tick() override;

	virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
	virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
	virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

	virtual void SaveToFile(ofstream& _File) override;
	virtual void LoadFromFile(ifstream& _File) override;

public:
	bool CheckState(TileState _State);

	int GetCamp() { return Camp; }
	bool GetVisible() { return IsVisible; }
	void SetTilePosition(int row, int col);

public:
	void SetTimer(TileState _State, float _Time);
	void AddTimer(TileState _State, float _Time);
	void ClearTimerAll();
	void ClearTimer(TileState _State);

public:
	CLONE(CTileScript);
	CTileScript();
	CTileScript(const CTileScript& _Origin);
	~CTileScript();

};
