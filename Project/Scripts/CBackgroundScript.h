#pragma once
#include <Engine/CScript.h>

class CBackgroundScript :
    public CScript
{
public:
    virtual void tick() override;


    virtual void SaveToFile(ofstream& _File) override;
    virtual void LoadFromFile(ifstream& _File) override;
    CLONE(CBackgroundScript);
public:
    CBackgroundScript();
    ~CBackgroundScript();
};

