#include "pch.h"

#include "CProjectileScript.h"
#include "CFieldScript.h"

#include <Engine/CGameObject.h>
#include <Engine/CComponent.h>

CProjectileScript::CProjectileScript()
	:CScript((UINT)SCRIPT_TYPE::PROJECTILESCRIPT)
{
}

CProjectileScript::CProjectileScript(UINT _ProjType)
	: CScript(_ProjType)
	, m_Shooter(nullptr)
	, m_ProjInfo{}
	, m_CurField(nullptr)
{
}

CProjectileScript::CProjectileScript(const CProjectileScript& _Origin)
	: CScript(_Origin)
	, m_Shooter(nullptr)
	, m_ProjInfo(_Origin.m_ProjInfo)
	, m_CurField(_Origin.m_CurField)
{
}

CProjectileScript::~CProjectileScript()
{
}


Proj_Struct::Proj_Struct()
{
	m_Speed =  1.f;
	Damage = 1.f;
	MaxRange = -1;

	LifeCount = -1;
	LifeTime = 10.f;


	TargetTile = false;
}

void CProjectileScript::Shoot(CGameObject* Shooter, CFieldScript* CurField, Proj_Struct& Info)
{
	// 외부 세팅. 사격자, 시작 인덱스
	SetOuterOption(Shooter, CurField);

	// 위치 재설정. Z축만 proj쪽으로 올려버리기
	ResetProjTransform(Vec2{ 10.f, 0.f });

	//정보 세팅
	this->SetInfo(Info);
}

void CProjectileScript::Move(float _DT)
{
	Vec3 ProjPosition = Transform()->GetRelativePos(); // 현재 투사체 위치
	float MoveDistance = m_ProjInfo.m_Speed * _DT; // 이동 거리 (속도 * 시간)

	// ShootDir이 정규화된 벡터라면, 각 성분에 이동 거리를 곱하여 이동 벡터를 계산
	Vec3 MoveVector = ShootDir * MoveDistance;

	// 새로운 위치 계산
	ProjPosition += MoveVector;

	// 투사체의 위치 업데이트
	Transform()->SetRelativePos(ProjPosition);

}

void CProjectileScript::SetOuterOption(CGameObject* Object, CFieldScript* CurrentField)
{
	this->SetShooter(Object);
	this->SetStartIdx(Object->GetScript<CFieldObjScript>()->GetOwnerIdx());
	this->SetField(CurrentField);
}

void CProjectileScript::ResetProjTransform(Vec2 Transform)
{
	Vec3 ProjTransform = this->GetShooter()->Transform()->GetWorldPos();
	ProjTransform.x += Transform.x;
	ProjTransform.y += Transform.y;
	ProjTransform.z = ProjectileZ;
	this->GetOwner()->Transform()->SetRelativePos(ProjTransform);
}

void CProjectileScript::CalculateDir(Vec2 StartIdx, Vec2 TargetDir)
{
	ShootDirIdx = TargetDir + StartIdx;

	Vec3 SpawnPostion = Transform()->GetRelativePos();
	Vec3 TargetDirection = this->GetField()->GetTilePosition(ShootDirIdx);

	TargetDirection -= SpawnPostion;
	TargetDirection.z = 0;
	TargetDirection.Normalize();

	
	Vec3 FrontDir = Vec3{ 1.f, 0.f, 0.f };

	if (m_Shooter->GetScript<CFieldObjScript>()->GetStatus().Camp == 2)
		FrontDir = -FrontDir;

	float cosTheta = FrontDir.Dot(TargetDirection);// cos(θ)
	float angle = acos(cosTheta); // θ

	Vec3 vRot = Transform()->GetRelativeRotation();

	// angle이 0이 아닌 경우에만 회전 적용
	if (fabs(angle) > 0.0001)
	{ // 부동 소수점 연산에서는 0과 정확히 일치하는 값을 비교하는 대신 작은 임계값을 사용
		

		// 방향성 고려 (예: 2D 게임에서 Z축 외적을 통해)
		Vec3 crossProd = FrontDir.Cross(TargetDirection);

		if (crossProd.z < 0)
		{
			angle = -angle; // 반시계 방향으로 회전
		}

		vRot.z += angle;// 여기서 angle은 라디안 단위

		// 변화된 회전값을 설정
		Transform()->SetRelativeRotation(vRot);
	}
	ShootDir = TargetDirection;
}

void CProjectileScript::begin()
{

}

void CProjectileScript::tick()
{
	float& lifetime = m_ProjInfo.LifeTime;

	lifetime -= DT;

	if (lifetime <= 0.f)
		this->GetOwner()->Destroy();

	Move(DT);
}


void CProjectileScript::SaveToFile(ofstream& _File)
{
}
void CProjectileScript::LoadFromFile(ifstream& _File)
{
}


