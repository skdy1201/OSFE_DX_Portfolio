#pragma once
#include "CMagic.h"

class AirSlash :
    public CMagic
{
private:
    Ptr<CPrefab> pWideShot;

public:

    virtual void cast(Vec2 StartPoint) override;
public:
    AirSlash();
    ~AirSlash();
};

