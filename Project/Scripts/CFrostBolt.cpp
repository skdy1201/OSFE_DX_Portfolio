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

	// 정보 세팅
	Proj_Struct Info = this->GetInfo();

	Info.Damage = 50;
	Info.MaxRange = 4;
	Info.LifeCount = -1;
	Info.LifeTime = 4.f;
	Info.TargetTile = false;
	Info.m_Speed = 5000.f;


	m_CurField;
	CalculateDir(StartIndex, Vec2{ 1, 0 });

	this->SetInfo(Info);

	Animator2D()->Play(L"FrostBlast", true);
	
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
