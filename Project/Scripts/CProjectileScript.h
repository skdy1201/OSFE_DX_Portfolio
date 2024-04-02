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


    Vec3            FrontDir;
    Vec3            ShootDir;

    bool            TargetTile;

public:
    Proj_Struct();

};

class CProjectileScript :
    public CScript
{
protected:
    CGameObject*    m_Shooter;
    CFieldScript*    m_CurField;
    Proj_Struct     m_ProjInfo;


    Vec2            StartIndex;
    Vec2            TargetIdx;

public:
    void SetStartIdx(Vec2 _index) { StartIndex = _index; }
    Vec2 GetStartIdx() { return TargetIdx; }

    void SetTargetIdx(Vec2 _index) { TargetIdx = _index; }
    Vec2 GetTargetIdx() { return TargetIdx; }

    void SetShooter(CGameObject* Shooter) { m_Shooter = Shooter; }
    CGameObject* GetShooter() { return m_Shooter; }

    void SetField(CFieldScript* _Field) { m_CurField = _Field; }
    CFieldScript* GetField() { return m_CurField; }

    void SetInfo(Proj_Struct _info) { m_ProjInfo = _info;}
    Proj_Struct GetInfo() { return m_ProjInfo; };

    void Shoot(CGameObject* Shooter, CFieldScript* CurField, Proj_Struct& Info);
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

