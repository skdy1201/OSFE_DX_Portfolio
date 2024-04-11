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

void CDeckCoverUI::MovetoHand()
{
	float movespeed = 300.f;


	if(PlayerScript->GetDeck()->GetQHand() != nullptr)
	{
		Qhand = PlayerScript->GetDeck()->GetQHand()->GetMagicIcon();

		Vec3 QDir = Hand1Pos - Qhand->Transform()->GetRelativePos();
		float QDistance = QDir.Length();

		QDir.Normalize();

		Vec3 QPos = Qhand->Transform()->GetRelativePos();
		QPos += QDir * movespeed * DT;

		if (QDistance < 1.f)
		{
			Qhand->Transform()->SetRelativePos(Hand1Pos);
		}
		else
		{
			Qhand->Transform()->SetRelativePos(QPos);
		}

	}

	if (PlayerScript->GetDeck()->GetWHand() != nullptr)
	{
		Whand = PlayerScript->GetDeck()->GetWHand()->GetMagicIcon();

		Vec3 WDir = Hand2Pos - Whand->Transform()->GetRelativePos();
		float WDistance = WDir.Length();
		WDir.Normalize();

		Vec3 WPos = Whand->Transform()->GetRelativePos();
		WPos += WDir * movespeed * DT;

		if (WDistance < 1.f)
		{
			Whand->Transform()->SetRelativePos(Hand2Pos);
		}
		else
		{
			Whand->Transform()->SetRelativePos(WPos);
		}
	}
}

void CDeckCoverUI::SetDeckleft()
{
	if(PlayerDeck->GetUnusedDeck().size() > 0)
	{
		for (int i = 0; i < PlayerDeck->GetUnusedDeck().size(); ++i)
		{
			Vec3 TargetPos = DeckCoverIn;
			TargetPos.y += (80.f * i);

			Vec3 Dir = TargetPos - PlayerDeck->GetUnusedDeck()[i]->GetMagicIcon()->Transform()->GetRelativePos();
			float Distance = Dir.Length();
			Dir.Normalize();

			Vec3 IconPos = PlayerDeck->GetUnusedDeck()[i]->GetMagicIcon()->Transform()->GetRelativePos();

			IconPos += Dir * 300.f * DT;

			if (Distance < 1.f)
			{
				PlayerDeck->GetUnusedDeck()[i]->GetMagicIcon()->Transform()->SetRelativePos(TargetPos);
			}
			else
			{
				PlayerDeck->GetUnusedDeck()[i]->GetMagicIcon()->Transform()->SetRelativePos(IconPos);
			}
		}
	}
}

void CDeckCoverUI::MovetoGrave()
{
	if (PlayerDeck->GetGrave().size() > 0)
	{
		for (int i = 0; i < PlayerDeck->GetGrave().size(); ++i)
		{
			Vec3 TargetDir = SpellGravesPos - PlayerDeck->GetGrave()[i]->Transform()->GetRelativePos();
			TargetDir.Normalize();

			Vec3 SpellCurPos = PlayerDeck->GetGrave()[i]->Transform()->GetRelativePos();

			float Dis = Vec3::Distance(SpellGravesPos, SpellCurPos);

			if (SpellCurPos.x > SpellGravesPos.x)
			{
				SpellCurPos += TargetDir * (Dis * 3) * DT;

				PlayerDeck->GetGrave()[i]->Transform()->SetRelativePos(SpellCurPos);
			}
			else
			{
				PlayerDeck->GetGrave()[i]->Transform()->SetRelativePos(SpellGravesPos);
			}

		}
	}
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
	MovetoHand();

	SetDeckleft();

	MovetoGrave();

}

void CDeckCoverUI::SaveToFile(ofstream& _File)
{
}

void CDeckCoverUI::LoadFromFile(ifstream& _File)
{
}
