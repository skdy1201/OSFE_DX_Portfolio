#include "pch.h"
#include "CDeckCoverUI.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include "CDeck.h"
#include "CFieldObjScript.h"
#include "CFieldScript.h"
#include "CMagic.h"

CDeckCoverUI::CDeckCoverUI()
	: CUIScript((UINT)SCRIPT_TYPE::DECKCOVERUI)
{
}

CDeckCoverUI::~CDeckCoverUI()
{
}

void CDeckCoverUI::begin()
{
	Player = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
	PlayerScript = Player->GetScript<CFieldObjScript>();
	pMagicmanager = PlayerScript->GetField()->magic_manager;

	Transform()->SetRelativePos(DeckCoverPos);

	for(int i = 0; i < pMagicmanager->GetMagicIconList().size(); ++i)
	{
		IconObjvector.push_back(pMagicmanager->GetMagicIconList()[i]);
		IconObjvector[i]->Transform()->SetRelativePos(SpellHidePos);
	}
}

void CDeckCoverUI::tick()
{
	int d = 0;
}

void CDeckCoverUI::SaveToFile(ofstream& _File)
{
}

void CDeckCoverUI::LoadFromFile(ifstream& _File)
{
}
