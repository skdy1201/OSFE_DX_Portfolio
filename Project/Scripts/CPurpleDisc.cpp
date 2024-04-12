#include "pch.h"
#include "CPurpleDisc.h"

#include "CRandomMgr.h"

CPurpleDisc::CPurpleDisc()
{
}

CPurpleDisc::CPurpleDisc(const CPurpleDisc& _Origin)
{
}

CPurpleDisc::~CPurpleDisc()
{
}

void CPurpleDisc::begin()
{
	// 정보 세팅
	Proj_Struct Info = this->GetInfo();

	Info.Damage = 50;
	Info.MaxRange = 4;
	Info.LifeCount = -1;
	Info.LifeTime = 6.f;
	Info.TargetTile = false;
	Info.m_Speed = 500.f;

	this->SetInfo(Info);

	ResetDir();

	Animator2D()->Play(PurpleDisc, true);
}

void CPurpleDisc::tick()
{
}

Vec2 CPurpleDisc::ResetDir()
{
	Vec2 dir = { 0, 0 };

	while(true)
	{
		Vec2 NextDir = this->GetTargetIdx();

		int Col = CRandomMgr::GetInst()->GetRandom(2);
		Col -= 1;

		NextDir.x += Col;

		int Row = CRandomMgr::GetInst()->GetRandom(2);
		Row -= 1;

		NextDir.y += Row;

		if(NextDir.x > 3 && NextDir.y > -1 &&
		   NextDir.x < 8 && NextDir.y <4)
		{
			dir = NextDir;
			break;
		}
	}

	return dir;
}

void CPurpleDisc::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CProjectileScript::BeginOverlap(_Collider, _OtherObj, _OtherCollider);
}

void CPurpleDisc::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CProjectileScript::Overlap(_Collider, _OtherObj, _OtherCollider);
}

void CPurpleDisc::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CProjectileScript::EndOverlap(_Collider, _OtherObj, _OtherCollider);
}