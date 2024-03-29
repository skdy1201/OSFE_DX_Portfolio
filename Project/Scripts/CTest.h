#pragma once

#include <Engine/CState.h>

class CTest :
    public CState
{
public:
    virtual void finaltick() {}
    virtual void Enter(){}
    virtual void Exit() {}
};

