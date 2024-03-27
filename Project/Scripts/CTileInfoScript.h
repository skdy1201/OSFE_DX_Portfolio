#pragma once
#include <Engine/CScript.h>
#include <Engine/components.h>



enum class TileChild
{
	InTile,
    Shadow,
    Break,
    Animator,
    End
};

enum class TileState
{
    Normal,
    On,
    Breaking,
    Break,
    Burn,
    End,
};


class CTileInfoScript :
    public CScript
{
private:
    int                  Camp;
    pair<int, int>       RowCol;
    UINT                 CurState;
    bool                 IsVisible;

    CGameObject*         TileChild[(int)TileChild::End];

    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(ofstream& _File) override;
    virtual void LoadFromFile(ifstream& _File) override;


    int GetCamp() { return Camp; }
    pair<int, int> GetRowCol() { return RowCol; }
	TileState GetTileState() { return (TileState)CurState; }
    bool      GetVisible() { return IsVisible; }
    CGameObject* GetTileChild() { return TileChild[0]; }


    void SpawnTile();
    CLONE(CTileInfoScript);

public:
    CTileInfoScript();
    CTileInfoScript(const CTileInfoScript& _Origin);
    ~CTileInfoScript();

};

