#include "pch.h"
#include "CTitleUI.h"

#include <Engine/CFontMgr.h>
#include <Engine/CRenderMgr.h>

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
	tFont menu1 = {};

	menu1.Message = L"Game Play";

	menu1.xscale = 100.f;
	menu1.yscale = 100.f;

	menu1.Fontsize = 50;

	menu1.RColor = 255.f;
	menu1.GColor = 255.f;
	menu1.BColor = 255.f;
	menu1.AColor = 1.f;

	CRenderMgr::GetInst()->AddFont(menu1);



}

void CTitleUI::SaveToFile(ofstream& _File)
{
	CUIScript::SaveToFile(_File);
}

void CTitleUI::LoadFromFile(ifstream& _File)
{
	CUIScript::LoadFromFile(_File);
}
