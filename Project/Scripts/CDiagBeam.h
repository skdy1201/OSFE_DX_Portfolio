#pragma once
#include "CProjectileScript.h"

class CDiagBeam :
    public CProjectileScript
{
private:

    Vec2 NextTileIdx;
    Vec3 StartMovePos;
    Vec3 NextTilePos;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

public:

    CDiagBeam();
    CDiagBeam(const CDiagBeam& _Origin);
    ~CDiagBeam();
    CLONE(CDiagBeam);
};

