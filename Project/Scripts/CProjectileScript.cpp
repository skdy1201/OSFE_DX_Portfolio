#include "pch.h"

#include "CProjectileScript.h"
#include "CFieldScript.h"

#include <Engine/CGameObject.h>
#include <Engine/CComponent.h>


CProjectileScript::CProjectileScript()
	: CScript((UINT)SCRIPT_TYPE::PROJECTILESCRIPT)
	, m_Shooter(nullptr)
	, m_ProjInfo{}
	, m_CurField(nullptr)
{
}

CProjectileScript::CProjectileScript(const CProjectileScript& _Origin)
	: CScript((UINT)SCRIPT_TYPE::PROJECTILESCRIPT)
	, m_Shooter(nullptr)
	, m_ProjInfo(_Origin.m_ProjInfo)
	, m_CurField(_Origin.m_CurField)
{
}

CProjectileScript::~CProjectileScript()
{
}

void CProjectileScript::FillInfo( float _Speed, int _Dmg, int _Range, float _Life, Vec2 _Index,
	Vec2 _DirIdx, bool IsTile)
{

	SetSpeed(_Speed);
	SetDamage(_Dmg);
	SetMaxRange(_Range);
	SetLife(_Life);
	SetIndex(_Index);
	SetTargetIdx(_DirIdx);
	SetTargetTile(IsTile);
}

void CProjectileScript::Move(float _DT)
{
	
	Vec3 ProjPosition = Transform()->GetRelativePos();
	ProjPosition += m_ProjInfo.ShootDir * (TileX + Tilespacex)  * (TileY + Tilespacey) * (m_ProjInfo.m_Speed * _DT);

	Transform()->SetRelativePos(ProjPosition);

}

void CProjectileScript::begin()
{
	if(m_Shooter != nullptr)
	{
	
		Vec2 SpawnIdx = m_ProjInfo.CurIndex;
		Vec2 TargetIdx = SpawnIdx + Vec2{ 1, 0 };

		Vec3 TargetDirection = m_CurField->GetTilePosition(TargetIdx);
		Vec3 SpawnPostion = Transform()->GetRelativePos();

		m_ProjInfo.FrontDir = Transform()->GetWorldDir(DIR_TYPE::FRONT);

		TargetDirection -= SpawnPostion;
		TargetDirection.z = 0;
		TargetDirection.Normalize();

		m_ProjInfo.FrontDir.Dot(TargetDirection);

		float cosTheta = m_ProjInfo.FrontDir.Dot(TargetDirection); // cos(θ)
		float angle = acos(cosTheta); // θ

		Vec3 vRot = Transform()->GetRelativeRotation();

			/*대각선일때 활성화 시키자
		 *vRot.z += -(angle / 2);*/

		Transform()->SetRelativeRotation(vRot);

		m_ProjInfo.ShootDir = TargetDirection;
		FillInfo(1.0f, 50, 3, 1, SpawnIdx, TargetIdx, false);
	}
}

void CProjectileScript::tick()
{
	Move(DT);
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