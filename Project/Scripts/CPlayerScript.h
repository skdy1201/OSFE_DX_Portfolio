#pragma once

#include <Engine/CScript.h>

class CPlayerScript :
    public CScript
{
private:
    Ptr<CPrefab>    m_Missile;
    float           m_Speed;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);


    virtual void SaveToFile(ofstream& _File) override;
    virtual void LoadFromFile(ifstream& _File) override;
    CLONE(CPlayerScript);
public:
    CPlayerScript();
    ~CPlayerScript();
};

