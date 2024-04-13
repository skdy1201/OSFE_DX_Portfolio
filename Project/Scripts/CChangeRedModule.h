#pragma once
#include "CAnimatorModule.h"

class CChangeRedModule :
    public CAnimatorModule
{
private:

    float    ChangeTime;

    float    ChangeColorR;
    float    ChangeColorG;
    float    ChangeColorB;
public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(ofstream& _File) override;
    virtual void LoadFromFile(ifstream& _File) override;
    CLONE(CChangeRedModule);
public:
    CChangeRedModule();
    ~CChangeRedModule();
};

