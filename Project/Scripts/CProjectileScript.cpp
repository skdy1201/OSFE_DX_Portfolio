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


void CProjectileScript::Move(float _DT)
{
	
	Vec3 ProjPosition = Transform()->GetRelativePos();
	ProjPosition += m_ProjInfo.ShootDir * (TileX + Tilespacex)  * (TileY + Tilespacey) * (m_ProjInfo.m_Speed * _DT);

	Transform()->SetRelativePos(ProjPosition);

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


