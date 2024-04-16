#pragma once
#include "CFieldObjScript.h"

class CTerraScript :
    public CFieldObjScript
{
    float            m_MoveCooltime;
    float            m_AttackCooltime;
    float            m_HurtTime;

    CFieldObjScript* OwnerFojScript;

    bool            bMovedbyAttack;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Hit(int Damage) override;

    bool   GetMovedByAttack() { return bMovedbyAttack; }


    virtual void SaveToFile(ofstream& _File) override;
    virtual void LoadFromFile(ifstream& _File) override;
    CLONE(CTerraScript);
public:
    CTerraScript();
    ~CTerraScript();
};

