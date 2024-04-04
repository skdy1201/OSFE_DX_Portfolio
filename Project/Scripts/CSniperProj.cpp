#include "pch.h"
#include "CSniperProj.h"

CSniperProj::CSniperProj()
	:  CProjectileScript((UINT)SCRIPT_TYPE::SNIPERPROJ)
{
}

CSniperProj::CSniperProj(const CSniperProj& _Origin)
	: CProjectileScript((UINT)SCRIPT_TYPE::SNIPERPROJ)
{
}

CSniperProj::~CSniperProj()
{
}

void CSniperProj::begin()
{
	// ���� ����
	Proj_Struct Info = this->GetInfo();

	Info.Damage = 50;
	Info.MaxRange = 4;
	Info.LifeCount = -1;
	Info.LifeTime = 4.f;
	Info.TargetTile = false;
	Info.m_Speed = 3000.f;

	CalculateDir(StartIndex, Vec2{ 1, 0 });

	this->SetInfo(Info);

	//Animator2D()->Play(L"FrostBlast", true);
}

void CSniperProj::tick()
{
	CProjectileScript::tick();
}

void CSniperProj::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CProjectileScript::BeginOverlap(_Collider, _OtherObj, _OtherCollider);
}

void CSniperProj::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CProjectileScript::Overlap(_Collider, _OtherObj, _OtherCollider);
}

void CSniperProj::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CProjectileScript::EndOverlap(_Collider, _OtherObj, _OtherCollider);
}
