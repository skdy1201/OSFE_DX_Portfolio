#include "pch.h"
#include "CFrostBolt.h"

#include "CFieldScript.h"
#include "CFieldObjScript.h"

CFrostBolt::CFrostBolt()
	:CProjectileScript((UINT)SCRIPT_TYPE::FROSTBOLT)
{
	
}

CFrostBolt::CFrostBolt(const CFrostBolt& _Origin)
	:CProjectileScript((UINT)SCRIPT_TYPE::FROSTBOLT)
{


}

CFrostBolt::~CFrostBolt()
{
}

void CFrostBolt::begin()
{

	CProjectileScript::begin();

	m_ProjInfo.LifeTime = 10.f;
	m_ProjInfo.m_Speed = 1.f;

	Animator2D()->Play(L"FrostBlast", true);
	TargetIdx = Vec2{ 1, 0 };

	m_CurField = m_Shooter->GetScript<CFieldObjScript>()->GetField();

	Vec2 TargetIdx = StartIndex + Vec2{ 1, 0 };
	Vec3 TargetDirection = m_CurField->GetTilePosition(TargetIdx);

	m_ProjInfo.FrontDir = Transform()->GetWorldDir(DIR_TYPE::FRONT);

	Vec3 SpawnPostion = Transform()->GetRelativePos();
	TargetDirection -= SpawnPostion;
	TargetDirection.z = 0;
	TargetDirection.Normalize();

	m_ProjInfo.FrontDir.Dot(TargetDirection);
	m_ProjInfo.ShootDir = m_ProjInfo.FrontDir;
	
}

void CFrostBolt::tick()
{
	CProjectileScript::tick();
}

void CFrostBolt::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CProjectileScript::BeginOverlap(_Collider, _OtherObj, _OtherCollider);
}

void CFrostBolt::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CProjectileScript::Overlap(_Collider, _OtherObj, _OtherCollider);
}

void CFrostBolt::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CProjectileScript::EndOverlap(_Collider, _OtherObj, _OtherCollider);
}
