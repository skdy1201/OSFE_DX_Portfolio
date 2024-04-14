#pragma once
#include "CMagic.h"

class BossDiscMagic :
    public CMagic
{
private:
    Ptr<CPrefab> PurpleDiscProj;

public:

    virtual void cast(Vec2 StartPoint) override;
public:
    BossDiscMagic();
    ~BossDiscMagic();
};

