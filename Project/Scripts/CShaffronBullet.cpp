#include "pch.h"
#include "CShaffronBullet.h"

#include "CFieldScript.h"

CShaffronBullet::CShaffronBullet()
	: CProjectileScript((UINT)SCRIPT_TYPE::SHAFFRONBULLET)
{
}

CShaffronBullet::CShaffronBullet(const CShaffronBullet& _Origin)
	: CProjectileScript((UINT)SCRIPT_TYPE::SHAFFRONBULLET)
{
}

CShaffronBullet::~CShaffronBullet()
{
}

void CShaffronBullet::begin()
{
	this->GetOwner()->Transform()->SetOffset(Vec2{ 0.f, 80.f });

	if (this->GetShooter() != nullptr)
	{
		// 정보 세팅
		Proj_Struct Info = this->GetInfo();

		Info.Damage = 50;
		Info.MaxRange = 4;
		Info.LifeCount = -1;
		Info.LifeTime = 4.f;
		Info.TargetTile = false;
		Info.m_Speed = 3000.f;
		TargetDir = Vec2{ 1, 0 };

		CalculateDir(StartIndex, TargetDir);

		this->SetInfo(Info);

	}
}

void CShaffronBullet::tick()
{
	CProjectileScript::tick();
}

void CShaffronBullet::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CShaffronBullet::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CShaffronBullet::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}
