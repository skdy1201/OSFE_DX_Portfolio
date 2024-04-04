#pragma once
#include "CProjectileScript.h"

class CSniperProj :
    public CProjectileScript
{

    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

public:

    CSniperProj();
    CSniperProj(const CSniperProj& _Origin);
    ~CSniperProj();
    CLONE(CSniperProj);
};

