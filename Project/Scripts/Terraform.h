#pragma once
#include "CMagic.h"
class Terraform :
    public CMagic
{
private:
    CGameObject* TerraBeam;

public:

    virtual void cast(Vec2 StartPoint) override;
public:
    Terraform();
    ~Terraform();
};

