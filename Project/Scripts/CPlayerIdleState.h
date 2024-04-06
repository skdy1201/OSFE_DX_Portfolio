#pragma once

#include <Engine/CState.h>

class CFieldObjScript;


class CPlayerIdleState :
    public CState
{
private:

    CGameObject*        Player;
    CFieldObjScript*    PlayerScript;

    float*              MoveTimer;
    float*              AttackTimer;

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CPlayerIdleState();
    ~CPlayerIdleState();
};

