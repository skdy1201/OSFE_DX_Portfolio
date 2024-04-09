#pragma once
#include "CUIScript.h"

class CManaBackGroundUIScript :
    public CUIScript
{
private:

    CGameObject* Player;
    int          PlayerMana;
    bool         ManaChange;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(ofstream& _File) override;
    virtual void LoadFromFile(ifstream& _File) override;
    CLONE(CManaBackGroundUIScript);
public:
    CManaBackGroundUIScript();
    ~CManaBackGroundUIScript();
};

