#pragma once
#include "CUIScript.h"

class CTitleUI :
    public CUIScript
{
private:

    wchar_t Menu1[50];
    wchar_t Menu2[50];

    CGameObject* LineObject;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(ofstream& _File) override;
    virtual void LoadFromFile(ifstream& _File) override;
    CLONE(CTitleUI);
public:
    CTitleUI();
    ~CTitleUI();
};

