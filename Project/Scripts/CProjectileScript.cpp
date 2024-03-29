#include "pch.h"

#include "CProjectileScript.h"

CProjectileScript::CProjectileScript()
	: CScript((UINT)SCRIPT_TYPE::PROJECTILESCRIPT)
	, m_Shooter(nullptr)
	, m_Speed(0.f)
	, Damage(0)
	, MaxRange(0)
	, CurIndex(0.f, 0.f)
{
}

CProjectileScript::CProjectileScript(const CProjectileScript& _Origin)
	: CScript((UINT)SCRIPT_TYPE::PROJECTILESCRIPT)
{
}

CProjectileScript::~CProjectileScript()
{
}

void CProjectileScript::FillInfo(CGameObject* _Target, float _Speed, int _Dmg, int _Range, Vec2 _Index)
{
	SetShooter(_Target);
	SetSpeed(_Speed);
	SetDamage(_Dmg);
	SetMaxRange(_Range);
	SetIndex(_Index);
}

void CProjectileScript::Move(float _DT)
{
	Vec3 Position = m_Owner->Transform()->GetWorldPos();


	if (m_Type == Bullet_Type::straight)
	{
		Position.x += _DT;
	}

	m_Owner->Transform()->SetRelativePos(Position);
}

void CProjectileScript::begin()
{
}

void CProjectileScript::tick()
{
}

void CProjectileScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CProjectileScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CProjectileScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CProjectileScript::SaveToFile(ofstream& _File)
{
}

void CProjectileScript::LoadFromFile(ifstream& _File)
{
}