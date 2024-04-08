#pragma once

#include "CAnimatorModule.h"

class CHitAnimationModule :
    public CAnimatorModule
{
private:
    int MaxBound;

    int MaxPos;

public:

    void SetRandomPos();
    void SetRandomScale();

    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(ofstream& _File) override;
    virtual void LoadFromFile(ifstream& _File) override;
    CLONE(CHitAnimationModule);
public:
    CHitAnimationModule();
    ~CHitAnimationModule();
};

