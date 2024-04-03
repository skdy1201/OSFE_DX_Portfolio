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
	// �ܺ� ����. �����, ���� �ε���
	SetOuterOption(Shooter, CurField);

	// ��ġ �缳��. Z�ุ proj������ �÷�������
	ResetProjTransform(Vec2{ 10.f, 0.f });

	//���� ����
	this->SetInfo(Info);
}

void CProjectileScript::Move(float _DT)
{
	Vec3 ProjPosition = Transform()->GetRelativePos(); // ���� ����ü ��ġ
	float MoveDistance = m_ProjInfo.m_Speed * _DT; // �̵� �Ÿ� (�ӵ� * �ð�)

	// ShootDir�� ����ȭ�� ���Ͷ��, �� ���п� �̵� �Ÿ��� ���Ͽ� �̵� ���͸� ���
	Vec3 MoveVector = ShootDir * MoveDistance;

	// ���ο� ��ġ ���
	ProjPosition += MoveVector;

	// ����ü�� ��ġ ������Ʈ
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

	float cosTheta = FrontDir.Dot(TargetDirection);// cos(��)
	float angle = acos(cosTheta); // ��

	Vec3 vRot = Transform()->GetRelativeRotation();

	// angle�� 0�� �ƴ� ��쿡�� ȸ�� ����
	if (fabs(angle) > 0.0001)
	{ // �ε� �Ҽ��� ���꿡���� 0�� ��Ȯ�� ��ġ�ϴ� ���� ���ϴ� ��� ���� �Ӱ谪�� ���
		

		// ���⼺ ��� (��: 2D ���ӿ��� Z�� ������ ����)
		Vec3 crossProd = FrontDir.Cross(TargetDirection);

		if (crossProd.z < 0)
		{
			angle = -angle; // �ݽð� �������� ȸ��
		}

		vRot.z += angle;// ���⼭ angle�� ���� ����

		// ��ȭ�� ȸ������ ����
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


