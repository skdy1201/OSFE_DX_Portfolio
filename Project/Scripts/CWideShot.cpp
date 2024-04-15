#include "pch.h"
#include "CWideShot.h"

#include "CFieldObjScript.h"

CWideShot::CWideShot()
{
}

CWideShot::~CWideShot()
{
}

void CWideShot::begin()
{
	// 정보 세팅
	Proj_Struct Info = this->GetInfo();

	Info.Damage = 20;
	Info.MaxRange = 4;
	Info.LifeCount = -1;
	Info.LifeTime = 3.5f;
	Info.TargetTile = false;
	Info.m_Speed = 650.f;

	this->SetInfo(Info);


	Animator2D()->Play(L"wideshot", true);
}


void CWideShot::tick()
{
	Move(DT);


	m_ProjInfo.LifeTime -= DT;

	if (m_ProjInfo.LifeTime <= 0.f)
		GamePlayStatic::DestroyGameObject(this->GetOwner());
}

void CWideShot::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	_OtherObj->GetScript<CFieldObjScript>()->SetMovedIdx(Vec2{ 1, 0 });
	_OtherObj->GetScript<CFieldObjScript>()->MovedByAttack();

	_OtherObj->GetScript<CFieldObjScript>()->Hit(this->GetInfo().Damage);

}

void CWideShot::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CProjectileScript::Overlap(_Collider, _OtherObj, _OtherCollider);
}

void CWideShot::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CProjectileScript::EndOverlap(_Collider, _OtherObj, _OtherCollider);
}
