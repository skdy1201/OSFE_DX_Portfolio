#pragma once

#include <Engine/CScript.h>

class CFieldScript;

struct Proj_Struct
{

    float           m_Speed;
    int             Damage;
    int             MaxRange;

    float           LifeCount;
    float           LifeTime;

    Vec2            StartIndex;
    Vec2            TargetIdx;

    Vec3            FrontDir;
    Vec3            ShootDir;

    bool            TargetTile;
};

class CProjectileScript :
    public CScript
{
private:
    CGameObject*    m_Shooter;
    CFieldScript*    m_CurField;
    Proj_Struct     m_ProjInfo;

public:
    void SetShooter(CGameObject* Shooter) { m_Shooter = Shooter; }
    CGameObject* GetShooter() { return m_Shooter; }

    void SetField(CFieldScript* _Field) { m_CurField = _Field; }
    CFieldScript* GetField() { return m_CurField; }

    void SetInfo(Proj_Struct _info) { m_ProjInfo = _info;}
    Proj_Struct GetInfo() { return m_ProjInfo; };

    void Move(float _DT);

    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {};
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {};
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {};


    virtual void SaveToFile(ofstream& _File) override;
    virtual void LoadFromFile(ifstream& _File) override;

public:
    CProjectileScript();
    CProjectileScript(UINT _ProjType);
    CProjectileScript(const CProjectileScript& _Origin);
    ~CProjectileScript();
    CLONE(CProjectileScript);
};

