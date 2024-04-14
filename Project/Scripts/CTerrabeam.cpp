#include "pch.h"
#include "CTerrabeam.h"

#include <Engine/CAnim.h>

#include "CFieldObjScript.h"


CTerrabeam::CTerrabeam()
	: CAnimatorModule((UINT)SCRIPT_TYPE::TERRABEAM)
{
}

CTerrabeam::~CTerrabeam()
{
}

void CTerrabeam::begin()
{
	CAnimatorModule::begin();
	count = 1;
}

void CTerrabeam::tick()
{
	OwnerAnimator->PlayModule(TerraformingAnim, count);


	if(OwnerAnimator->GetCurAnim()->IsFinish())
	{
		GamePlayStatic::DestroyGameObject(pObj);
	}
}

void CTerrabeam::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{

	CFieldObjScript* Script;

	if(Script = _OtherObj->GetScript<CFieldObjScript>())
	{
		Script->Hit(50);
	}

}

void CTerrabeam::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CTerrabeam::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CTerrabeam::SaveToFile(ofstream& _File)
{
	CAnimatorModule::SaveToFile(_File);
}

void CTerrabeam::LoadFromFile(ifstream& _File)
{
	CAnimatorModule::LoadFromFile(_File);
}
