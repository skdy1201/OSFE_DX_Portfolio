#pragma once
#include "CFieldObjScript.h"

class CTerraScript :
    public CFieldObjScript
{
    float            m_MoveCooltime;
    float            m_AttackCooltime;
    float            m_HurtTime;
    int              CurRow;
    int              MoveDir; // 1 :: down, 2 :: up



    CFieldObjScript* OwnerFojScript;
    CGameObject*    ChildAnim;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Hit(int Damage) override;



    virtual void SaveToFile(ofstream& _File) override;
    virtual void LoadFromFile(ifstream& _File) override;
    CLONE(CTerraScript);
public:
    CTerraScript();
    ~CTerraScript();
};

