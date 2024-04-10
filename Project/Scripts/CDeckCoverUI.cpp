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
	, FirstSet(true)
{
}

CDeckCoverUI::~CDeckCoverUI()
{
}

void CDeckCoverUI::begin()
{
	Player = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
	PlayerScript = Player->GetScript<CFieldObjScript>();
	PlayerDeck = PlayerScript->GetDeck();


	Transform()->SetRelativePos(DeckCoverPos);


}

void CDeckCoverUI::tick()
{
	CMagic* Hand1 = PlayerScript->GetDeck()->GetQHand();
	CMagic* Hand2 = PlayerScript->GetDeck()->GetWHand();

	//처음만 세팅
	if(FirstSet == true &&
		PlayerDeck->GetMagicList().size() > 0
		&& PlayerDeck->GetWHand() != nullptr
		&& PlayerDeck->GetQHand() != nullptr)
	{

		Hand1->GetMagicIcon()->Transform()->SetRelativePos(Hand1Pos);

		Hand2->GetMagicIcon()->Transform()->SetRelativePos(Hand2Pos);

		for(int i = 0; i < PlayerDeck->GetUnusedDeck().size(); ++i)
		{
			Vec3 IconOffset = Vec3{ 0.f, (80.f * i), 0.f };
			Vec3 IconPos = DeckCoverIn;

			PlayerDeck->GetUnusedDeck()[i]->GetMagicIcon()->Transform()->SetRelativePos(IconPos + IconOffset);
		}

		FirstSet = false;
	}

	if(PlayerDeck->GetUseHand())
	{
		Vec3 Dir = { 0.f, -1.f, 0.f };
		Dir.Normalize();

		Vec3 point1(0.f, 0.f, 0.f);
		Vec3 point2(0.f, -80.f, 0.f);
		float distance = Vec3::Distance(point1, point2);

		for(int i = 0; i  < PlayerDeck->GetUnusedDeck().size(); ++i)
		{
			Vec3 IconPos = PlayerDeck->GetUnusedDeck()[i]->GetMagicIcon()->Transform()->GetRelativePos();

			if(IconPos.y >= (DeckCoverIn.y + (80.f * i)))
			{
				IconPos += Dir * distance * 2 * DT;
				PlayerDeck->GetUnusedDeck()[i]->GetMagicIcon()->Transform()->SetRelativePos(IconPos);
			}
			else
			{
				PlayerDeck->GetUnusedDeck()[i]->GetMagicIcon()->Transform()->SetRelativePos(IconPos);

				if (i == PlayerDeck->GetUnusedDeck().size() - 1)
					PlayerDeck->SetUseHand(false);

			}

			
		}
	}


}

void CDeckCoverUI::SaveToFile(ofstream& _File)
{
}

void CDeckCoverUI::LoadFromFile(ifstream& _File)
{
}
