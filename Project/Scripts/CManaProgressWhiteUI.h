#pragma once
#include "CUIScript.h"


class CFieldObjScript;

class CManaProgressWhiteUI :
    public CUIScript
{
    CFieldObjScript* PlayerScript;


    float MaxMana;
    float CurrentMana;
    float ManaRegen;


public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(ofstream& _File) override;
    virtual void LoadFromFile(ifstream& _File) override;
    CLONE(CManaProgressWhiteUI);
public:
    CManaProgressWhiteUI();
    ~CManaProgressWhiteUI();
};

