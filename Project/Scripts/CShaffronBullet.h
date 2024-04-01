#pragma once

#include "CProjectileScript.h"

class CShaffronBullet :
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

    CShaffronBullet();
    CShaffronBullet(const CShaffronBullet& _Origin);
    ~CShaffronBullet();
    CLONE(CShaffronBullet);
};

