#pragma once

#include <Engine/CState.h>

class CFieldObjScript;
class CFieldScript;


class CPlayerMoveState :
    public CState
{
private:
    CGameObject* Player;
    CFieldObjScript* PlayerScript;
    CFieldScript* Field;

    Vec2   NextIdx;
    Vec2   MoveIdx;
    Vec3   TargetPos;
    float MovingTime;

    float Distance;
    float Speed;

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CPlayerMoveState();
    ~CPlayerMoveState();
};

