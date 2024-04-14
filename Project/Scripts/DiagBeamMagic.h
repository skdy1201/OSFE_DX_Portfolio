#pragma once
#include "CMagic.h"

class DiagBeamMagic :
    public CMagic
{
private:
    Ptr<CPrefab> DiagBeam;

public:
    virtual void cast(Vec2 StartPoint) override;

public:
    DiagBeamMagic();
    ~DiagBeamMagic();
};

