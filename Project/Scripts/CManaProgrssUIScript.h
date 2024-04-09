#pragma once
#include "CUIScript.h"

class CManaProgrssUIScript :
    public CUIScript
{
    CGameObject* Owner;

    float         MaxMana;
    float         CurMana;
    float         ManaRegen;

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

