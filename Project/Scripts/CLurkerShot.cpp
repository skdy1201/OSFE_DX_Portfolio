#include "pch.h"
#include "CLurkerShot.h"

#include <Engine/CAnim.h>

#include "CFieldObjScript.h"

CLurkerShot::CLurkerShot()
	: CAnimatorModule((UINT)SCRIPT_TYPE::LURKERSCRIPT)
{
}

CLurkerShot::~CLurkerShot()
{
}

void CLurkerShot::begin()
{
	CAnimatorModule::begin();
	lefttime = 1.5f;
	OwnerAnimator->Play(L"LurkerShot1", false);
}

void CLurkerShot::tick()
{
	lefttime -= DT;

	if(lefttime <= 0.f)
	{
		GamePlayStatic::DestroyGameObject(pObj);
	}
}

void CLurkerShot::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CFieldObjScript* Script;

	if (Script = _OtherObj->GetScript<CFieldObjScript>())
	{
		Script->Hit(50);
	}
}

void CLurkerShot::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CAnimatorModule::Overlap(_Collider, _OtherObj, _OtherCollider);
}

void CLurkerShot::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CAnimatorModule::EndOverlap(_Collider, _OtherObj, _OtherCollider);
}

void CLurkerShot::SaveToFile(ofstream& _File)
{
	CAnimatorModule::SaveToFile(_File);
}

void CLurkerShot::LoadFromFile(ifstream& _File)
{
	CAnimatorModule::LoadFromFile(_File);
}
