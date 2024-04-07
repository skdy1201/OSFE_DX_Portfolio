#pragma once
#include "CAnimatorModule.h"

class CPlayerSpawnAnim :
    public CAnimatorModule
{
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(ofstream& _File) override;
    virtual void LoadFromFile(ifstream& _File) override;
    CLONE(CPlayerSpawnAnim);
public:
    CPlayerSpawnAnim();
    ~CPlayerSpawnAnim();
};

