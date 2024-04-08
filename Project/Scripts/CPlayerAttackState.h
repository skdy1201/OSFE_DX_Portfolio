#pragma once

#include <Engine/CScript.h>

class CFieldScript;
class CFieldObjScript;

class CPlayerAttackState :
    public CState
{
    CGameObject* Player;
    CFieldObjScript* PlayerScript;
    CFieldScript* Field;

    CGameObject* Bullet;

    float             AttackTimer;

    float             AttackRelayTimer;
    int               AnimationCount;

public:
    void Shoot(float _Dt);

    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CPlayerAttackState();
    ~CPlayerAttackState();
};

