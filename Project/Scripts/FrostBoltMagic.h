#pragma once
#include "CMagic.h"


class FrostBoltMagic :
    public CMagic
{
private:
    Ptr<CPrefab> FrostBolt;

public:

    virtual void cast(Vec2 StartPoint) override;
public:
    FrostBoltMagic();
    ~FrostBoltMagic();
};

