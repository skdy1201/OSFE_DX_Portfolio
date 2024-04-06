#pragma once

#include <Engine/CState.h>

class CFieldScript;
class CFieldObjScript;


class CPlayerIdleState :
    public CState
{
private:

    CGameObject*        Player;
    CFieldObjScript*    PlayerScript;
    CFieldScript*       Field;

    float             AttackTimer;

    float             AttackRelayTimer;


public:

    void Shoot(float _Dt);

    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CPlayerIdleState();
    ~CPlayerIdleState();
};

