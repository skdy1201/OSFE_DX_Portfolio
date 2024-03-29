#pragma once

#include <Engine/CScript.h>

enum class Bullet_Type
{
	straight,
    diagnal,
    upside,
    downside,
    back,
    Beam,

};

class CProjectileScript :
    public CScript
{
private:
    CGameObject*    m_Shooter;
    CGameObject*    m_Owner;


    float           m_Speed;
	int             Damage;
    int             MaxRange;

	Vec2            CurIndex;
    Bullet_Type     m_Type;

public:
    void SetShooter(CGameObject* _Shooter) { m_Shooter = _Shooter; }
    void SetSpeed(float _Speed) { m_Speed = _Speed; }
    void SetDamage(int Dmg) { Damage = Dmg; }
    void SetMaxRange(int _Range) { MaxRange = _Range; }
    void SetIndex(Vec2 _Idx) { CurIndex = _Idx; }

    void FillInfo(CGameObject* _Target, float _Speed, int _Dmg, int _Range, Vec2 _Index);

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

