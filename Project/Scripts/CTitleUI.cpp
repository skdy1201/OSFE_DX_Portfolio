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

	if(KEY_TAP(KEY::ENTER))
	{
		GamePlayStatic::Play2DSound(L"sound\\accept_soft.wav", 1, 0.5f, false);

		GamePlayStatic::DestroyGameObject(this->GetOwner());
	}
	

}

void CTitleUI::SaveToFile(ofstream& _File)
{
	CUIScript::SaveToFile(_File);
}

void CTitleUI::LoadFromFile(ifstream& _File)
{
	CUIScript::LoadFromFile(_File);
}
