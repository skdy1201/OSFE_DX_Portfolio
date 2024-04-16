#pragma once

#include <Engine/CState.h>

class CFieldScript;
class CTerraScript;

class CTerraMoveState :
    public CState
{
private:

    CFieldScript*       CurField;
    CTerraScript*    TerraScript;

    int                 MoveTime;

    queue<Vec2>         MoveIdxList;

    Vec2                TargetIdx;
    Vec3                TargetTilePos;

    float*              MoveCooldtime;

    bool                MoveComplete;
    

public:

    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CTerraMoveState();
    ~CTerraMoveState();
};

