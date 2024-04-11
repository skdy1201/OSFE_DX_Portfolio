#pragma once

#include <Engine/CScript.h>

class CFieldScript;
class CFieldObjScript;

class CPlayerHitState :
    public CState
{
    CGameObject* Player;
    CFieldObjScript* PlayerScript;
    CFieldScript* Field;

    bool IsRender;
    float Timer;

public:

    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CPlayerHitState();
    ~CPlayerHitState();

};

