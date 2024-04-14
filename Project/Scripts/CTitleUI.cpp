#include "pch.h"
#include "CTitleUI.h"

#include <Engine/CFontMgr.h>

CTitleUI::CTitleUI()
	: CUIScript((UINT)SCRIPT_TYPE::TITLEUI)
{
}

CTitleUI::~CTitleUI()
{
}

void CTitleUI::begin()
{
	CUIScript::begin();
}

void CTitleUI::tick()
{
	swprintf_s(Menu1, 50, L"Play Game");

	CFontMgr::GetInst()->DrawFont(Menu1, 150.f, 150.f, 20, FONT_RGBA(255, 30, 30, 255));



}

void CTitleUI::SaveToFile(ofstream& _File)
{
	CUIScript::SaveToFile(_File);
}

void CTitleUI::LoadFromFile(ifstream& _File)
{
	CUIScript::LoadFromFile(_File);
}
