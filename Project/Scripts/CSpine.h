#pragma once
#include "CAnimatorModule.h"


class CSpine :
    public CAnimatorModule
{
private:

    float lifetimer;

    float OverlapTime;

public:


    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

    virtual void SaveToFile(ofstream& _File) override;
    virtual void LoadFromFile(ifstream& _File) override;
    CLONE(CSpine);
public:
    CSpine();
    ~CSpine();
};

