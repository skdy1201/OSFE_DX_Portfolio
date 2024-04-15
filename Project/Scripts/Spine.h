#pragma once
#include "CMagic.h"

class Spine :
    public CMagic
{
private:
    CGameObject* pSpine;

public:

    virtual void cast(Vec2 StartPoint) override;
public:
    Spine();
    ~Spine();

};

