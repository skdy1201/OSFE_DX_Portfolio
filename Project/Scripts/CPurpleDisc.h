#pragma once
#include "CDiagBeam.h"
#include "CProjectileScript.h"

class CPurpleDisc :
    public CProjectileScript
{

public:

    Vec2 Dir[4];
    Vec2 CurDir;
    int Colignore;

public:
    void ResetDir();

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

public:

    CPurpleDisc();
    CPurpleDisc(const CPurpleDisc& _Origin);
    ~CPurpleDisc();
    CLONE(CPurpleDisc);
};

