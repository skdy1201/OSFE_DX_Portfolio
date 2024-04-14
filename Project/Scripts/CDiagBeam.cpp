#include "pch.h"
#include "CDiagBeam.h"

#include "CFieldScript.h"

CDiagBeam::CDiagBeam()
	: CProjectileScript((UINT)SCRIPT_TYPE::DIAGBEAM)
{

}

CDiagBeam::~CDiagBeam()
{



}

void CDiagBeam::begin()
{
	// 정보 세팅
	Proj_Struct Info = this->GetInfo();

	Info.Damage = 50;
	Info.MaxRange = 4;
	Info.LifeCount = 4;
	Info.LifeTime = 60.f;
	Info.TargetTile = false;
	Info.m_Speed = 600.f;

	this->SetInfo(Info);

	NextTileIdx =  Vec2{ -1, -1 };
	Vec2 FieldTileIdx = StartIndex + NextTileIdx;
	NextTilePos = m_CurField->GetTilePosition(FieldTileIdx);

	CalculateDir(StartIndex, NextTileIdx);

	StartMovePos = this->GetOwner()->Transform()->GetRelativePos();
	Animator2D()->Play(DiagBeamAnim, true);

}

void CDiagBeam::tick()
{

	if(m_ProjInfo.LifeCount > 0)
	{
		Move(DT);

		Vec3 CurPos = NextTilePos - Transform()->GetRelativePos();
		CurPos.x = abs(CurPos.x);
		CurPos.y = abs(CurPos.y);
		CurPos.z = abs(CurPos.z);
		if(CurPos.x < 1.f && CurPos.y < 1.f)
		{
			m_ProjInfo.LifeCount -= 1;
			StartIndex += NextTileIdx;

			Vec2 FieldTileIdx = { 0, 0 };

			switch (m_ProjInfo.LifeCount)
			{
			case 3:
				NextTileIdx =  Vec2{ 1, -1 };
				FieldTileIdx = StartIndex + NextTileIdx;
				NextTilePos = m_CurField->GetTilePosition(FieldTileIdx);
				CalculateDir(StartIndex, NextTileIdx);
				break;
			case 2:
				NextTileIdx =  Vec2{ 1, +1 };
				FieldTileIdx = StartIndex + NextTileIdx;
				NextTilePos = m_CurField->GetTilePosition(FieldTileIdx);
				CalculateDir(StartIndex, NextTileIdx);
				break;
			case 1:
				NextTileIdx =  Vec2{ -1, +1 };
				FieldTileIdx = StartIndex + NextTileIdx;
				NextTilePos = m_CurField->GetTilePosition(FieldTileIdx);
				CalculateDir(StartIndex, NextTileIdx);
				break;
			}
		}
		
	}
	else
	{
		GamePlayStatic::DestroyGameObject(this->GetOwner());
	}
}

void CDiagBeam::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	_OtherObj->GetScript<CFieldObjScript>()->Hit(this->GetInfo().Damage);
}

void CDiagBeam::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CProjectileScript::Overlap(_Collider, _OtherObj, _OtherCollider);
}

void CDiagBeam::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CProjectileScript::EndOverlap(_Collider, _OtherObj, _OtherCollider);
}

CDiagBeam::CDiagBeam(const CDiagBeam& _Origin)
	: CProjectileScript((UINT)SCRIPT_TYPE::DIAGBEAM)
{
}
