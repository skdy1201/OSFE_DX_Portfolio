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
	if (this->GetShooter() != nullptr)
	{
		Proj_Struct Info = this->GetInfo();

		Info.Damage = 50;
		Info.MaxRange = 4;
		Info.LifeCount = -1;
		Info.LifeTime = 4.f;
		Info.TargetTile = false;
		Info.m_Speed = 0.45f;

		Vec2 SpawnIdx = StartIndex;
		Vec2 TargetIdx = SpawnIdx + Vec2{ 1, 0 };

		Vec3 TargetDirection = this->GetField()->GetTilePosition(TargetIdx);
		Vec3 SpawnPostion = Transform()->GetRelativePos();

		Info.FrontDir = Transform()->GetWorldDir(DIR_TYPE::FRONT);

		TargetDirection -= SpawnPostion;
		TargetDirection.z = 0;
		TargetDirection.Normalize();

		Info.FrontDir.Dot(TargetDirection);

		float cosTheta = Info.FrontDir.Dot(TargetDirection); // cos(θ)
		float angle = acos(cosTheta); // θ

		Vec3 vRot = Transform()->GetRelativeRotation();


		//대각선일때 활성화 시키자
		// vRot.z += -(angle / 2);

		Transform()->SetRelativeRotation(vRot);

		Info.ShootDir = TargetDirection;

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
