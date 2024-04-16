#include "pch.h"
#include "CSpine.h"

#include <Engine/CAnim.h>

#include "CFieldObjScript.h"

CSpine::CSpine()
	: CAnimatorModule(((UINT)SCRIPT_TYPE::SPINE))
{
}

CSpine::~CSpine()
{
}

void CSpine::begin()
{
	CAnimatorModule::begin();

	lifetimer = 10.f;
	OverlapTime = 0.f;

}

void CSpine::tick()
{
	CAnimatorModule::tick();

	lifetimer -= DT;

	if (lifetimer <= 0.f)
		GamePlayStatic::DestroyGameObject(this->GetOwner());
}

void CSpine::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CFieldObjScript* Script;

	if (Script = _OtherObj->GetScript<CFieldObjScript>())
	{
		Script->Hit(15);
	}
}

void CSpine::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	OverlapTime += DT;

	if(OverlapTime >= 2.f)
	{
		CFieldObjScript* Script;

		if (Script = _OtherObj->GetScript<CFieldObjScript>())
		{
			Script->Hit(15);
		}

		OverlapTime = 0.f;
		
	}
}

void CSpine::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CAnimatorModule::EndOverlap(_Collider, _OtherObj, _OtherCollider);
}

void CSpine::SaveToFile(ofstream& _File)
{
	CAnimatorModule::SaveToFile(_File);
}

void CSpine::LoadFromFile(ifstream& _File)
{
	CAnimatorModule::LoadFromFile(_File);
}
