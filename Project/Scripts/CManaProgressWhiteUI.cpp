#include "pch.h"
#include "CManaProgressWhiteUI.h"

#include "CManaProgrssUIScript.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include "CFieldObjScript.h"

CManaProgressWhiteUI::CManaProgressWhiteUI()
	: CUIScript((UINT)SCRIPT_TYPE::MANAPROGRESSWHITEUI)
{
}

CManaProgressWhiteUI::~CManaProgressWhiteUI()
{
}

void CManaProgressWhiteUI::begin()
{
	CUIScript::begin();

	CGameObject* Player = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
	PlayerScript = Player->GetScript<CFieldObjScript>();

	Vec3 StartScale = Transform()->GetRelativeScale();
	StartScale.x = 0.f;

	Transform()->SetRelativeScale(StartScale);

	this->GetRenderComponent()->GetDynamicMaterial()->SetScalarParam(SCALAR_PARAM::VEC4_0, Vec4{ 1.f, 1.f, 1.f, 1.f });
}

void CManaProgressWhiteUI::tick()
{
	float ManaPercent = PlayerScript->GetMpPersent();

	Vec3 WScale = Transform()->GetRelativeScale();

	float targetScale = ManaPercent* ManaProgrssScaleX;
	float curScale = WScale.x;
	int increase;
	if(targetScale < curScale)
	{
		increase = -1;
		curScale += increase * 100.f * DT;
	}else
	{
		increase = 1;
		curScale = targetScale;
	}

	WScale.x = curScale;
	pObj->Transform()->SetRelativeScale(WScale);

	Vec2 Offset = { WScale.x / 2.f, 0.f };
	pObj->Transform()->SetOffset(Offset);
}

void CManaProgressWhiteUI::SaveToFile(ofstream& _File)
{
	CUIScript::SaveToFile(_File);
}

void CManaProgressWhiteUI::LoadFromFile(ifstream& _File)
{
	CUIScript::LoadFromFile(_File);
}
