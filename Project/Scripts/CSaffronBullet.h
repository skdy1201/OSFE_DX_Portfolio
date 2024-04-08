#pragma once

#include "CProjectileScript.h"

class CSaffronBullet :
    public CProjectileScript
{
private:

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

public:

    CSaffronBullet();
    CSaffronBullet(const CSaffronBullet& _Origin);
    ~CSaffronBullet();
    CLONE(CSaffronBullet);
};

