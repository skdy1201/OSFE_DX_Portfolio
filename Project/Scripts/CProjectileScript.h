#pragma once

#include <Engine/CScript.h>

class CFieldScript;

struct Proj_Struct
{

    float           m_Speed;
    int             Damage;
    int             MaxRange;

    float           LifeCount;

    Vec2            CurIndex;
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
    void SetShooter(CGameObject* _Shooter) { m_Shooter = _Shooter; }
    void SetSpeed(float _Speed) { m_ProjInfo.m_Speed = _Speed; }
    void SetDamage(int Dmg) { m_ProjInfo.Damage = Dmg; }
    void SetMaxRange(int _Range) { m_ProjInfo.MaxRange = _Range; }
    void SetLife(float _life) { m_ProjInfo.LifeCount = _life; }
    void SetIndex(Vec2 _Idx) { m_ProjInfo.CurIndex = _Idx; }
    void SetTargetIdx(Vec2 _DirIdx) { m_ProjInfo.TargetIdx = _DirIdx; }
    void SetTargetTile(bool IsTile) { m_ProjInfo.TargetTile = IsTile; }

    void SetField(CFieldScript* _Field) { m_CurField = _Field; }

    void FillInfo(float _Speed, int _Dmg, int _Range, float _Life, Vec2 _Index, Vec2 _DirIdx, bool IsTile);

    void Move(float _DT);

    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);


    virtual void SaveToFile(ofstream& _File) override;
    virtual void LoadFromFile(ifstream& _File) override;

public:
    CProjectileScript();
    CProjectileScript(const CProjectileScript& _Origin);
    ~CProjectileScript();
    CLONE(CProjectileScript);
};

