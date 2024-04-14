#include "pch.h"
#include "CSniperProj.h"

#include "CFieldObjScript.h"

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
	// 정보 세팅
	Proj_Struct Info = this->GetInfo();

	Info.Damage = 50;
	Info.MaxRange = 4;
	Info.LifeCount = -1;
	Info.LifeTime = 5.f;
	Info.TargetTile = false;
	Info.m_Speed = 3000.f;

	this->SetInfo(Info);

	Animator2D()->Play(L"Redball", true);
}

void CSniperProj::tick()
{
	CProjectileScript::tick();
}

void CSniperProj::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CFieldObjScript* Script = _OtherObj->GetScript<CFieldObjScript>();
	Script->Hit(this->GetInfo().Damage);

	this->GetOwner()->Destroy();
}

void CSniperProj::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CProjectileScript::Overlap(_Collider, _OtherObj, _OtherCollider);
}

void CSniperProj::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CProjectileScript::EndOverlap(_Collider, _OtherObj, _OtherCollider);
}
