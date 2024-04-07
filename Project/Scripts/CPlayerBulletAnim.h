#pragma once
#include "CAnimatorModule.h"

class CPlayerBulletAnim :
    public CAnimatorModule
{
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(ofstream& _File) override;
    virtual void LoadFromFile(ifstream& _File) override;
    CLONE(CPlayerBulletAnim);
public:
    CPlayerBulletAnim();
    ~CPlayerBulletAnim();
};

