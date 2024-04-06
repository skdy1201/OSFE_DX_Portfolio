#pragma once

#include <Engine/CState.h>

class CFieldObjScript;


class CPlayerMoveState :
    public CState
{
private:
    CGameObject* Player;
    CFieldObjScript* PlayerScript;

    float* MoveTimer;

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CPlayerMoveState();
    ~CPlayerMoveState();
};

