#pragma once

#include <Engine/CState.h>

class CFieldObjScript;

class CSniperMoveState :
    public CState
{
private:

    CFieldObjScript*    SniperScript;
    Vec2                m_OwnerIdx;
    int*                MoveDir;
    float*              MoveCooldtime;
    float*              AttackCooltime;

public:

    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CSniperMoveState();
    ~CSniperMoveState();
};


