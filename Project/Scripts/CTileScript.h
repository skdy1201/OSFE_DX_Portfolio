#pragma once

#include <Engine/CScript.h>
#include <Engine/components.h>


enum class TileChildType
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


class CTileScript :
    public CScript
{
    
private:
    int                  Camp;
    bool                 IsVisible;


    float     StateTimer[(int)TileState::End];
    CGameObject* TileChild[(int)TileChildType::End];

    Ptr<CMaterial>    TileMtrl;

public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(ofstream& _File) override;
    virtual void LoadFromFile(ifstream& _File) override;

public:

    bool        CheckState(TileState _State);

    int GetCamp() { return Camp; }
    bool      GetVisible() { return IsVisible; }
    CGameObject* GetTileChild(TileChildType _child) { return TileChild[(int)_child]; }
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

private:
    void SpawnChild();
};

