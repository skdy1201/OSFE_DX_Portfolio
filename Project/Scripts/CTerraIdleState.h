#pragma once

#include <Engine/CState.h>

class CFieldObjScript;

class CTerraIdleState :
    public CState
{private:

    CFieldObjScript*    TerraScript;
    
    float*              MoveCooldtime;
    float*              AttackCooltime;
public:

    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CTerraIdleState();
    ~CTerraIdleState();
};

