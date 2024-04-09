#pragma once
#include "CUIScript.h"

class CFieldObjScript;
struct Status;

class CManaProgrssUIScript :
    public CUIScript
{
    CGameObject*        Owner;
    CFieldObjScript*    OwnerScript;

    float MaxMana;
    float CurrentMana;
    float ManaRegen;


public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(ofstream& _File) override;
    virtual void LoadFromFile(ifstream& _File) override;
    CLONE(CManaProgrssUIScript);
public:
    CManaProgrssUIScript();
    ~CManaProgrssUIScript();

};

