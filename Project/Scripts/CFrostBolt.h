#pragma once
#include "CProjectileScript.h"
#include "CSaffronBullet.h"


class CFrostBolt :
    public CProjectileScript
{
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

public:

    CFrostBolt();
    CFrostBolt(const CFrostBolt& _Origin);
    ~CFrostBolt();
    CLONE(CFrostBolt);
};

