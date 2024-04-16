#pragma once

#include "CFieldObjScript.h"

class CLurkerScript :
    public CFieldObjScript
{
private:
    float            m_AttackCooltime;
    float            m_HurtTime;
    int              CurRow;

    bool            bMovedbyAttack;
    Vec2            MovedIdx;


public:

    bool   GetMovedByAttack() { return bMovedbyAttack; }


public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Hit(int Damage) override;



    virtual void SaveToFile(ofstream& _File) override;
    virtual void LoadFromFile(ifstream& _File) override;
    CLONE(CLurkerScript);
public:
    CLurkerScript();
    ~CLurkerScript();

};

