#pragma once

#include <Engine/CState.h>

class CSniperScript;

class CSniperMoveState :
    public CState
{
private:

    CSniperScript*    SniperScript;
    Vec2                m_OwnerIdx;
    int*                MoveDir;
    float*              MoveCooldtime;
    float*              AttackCooltime;


    Vec2                AttackMovedIdx;

public:

    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CSniperMoveState();
    ~CSniperMoveState();
};


