#include "pch.h"
#include "CDeck.h"

#include <Engine/CGameObject.h>

#include "CFieldObjScript.h"
#include "CMagic.h"
#include "CRandomMgr.h"

CDeck::CDeck()
	: IsShaffle(false)
{
}

CDeck::~CDeck()
{
	for (int i = 0; i < MagicList.size(); ++i)
	{
		if (MagicList[i] != nullptr)
			delete MagicList[i];
	}

	for (int j = 0; j < UnusedDeck.size(); ++j)
	{
		if (UnusedDeck[j] != nullptr)
			UnusedDeck[j] = nullptr;
	}
		if (QHand != nullptr)
			QHand = nullptr;

		if (WHand != nullptr)
			WHand = nullptr;
	
}

void CDeck::begin()
{

	auto iter = MagicList.begin();

	Shuffle();

	FillHand();
	FillHand();

	

}

void CDeck::FillHand()
{
	if(UnusedDeck.size() == 0 && QHand == nullptr && WHand == nullptr)
	{
		IsShaffle = true;
		Shuffle();
	}

	if(IsShaffle == true)
	{
		QHand = UnusedDeck.front();
		UnusedDeck.pop_front();

		WHand = UnusedDeck.front();
		UnusedDeck.pop_front();

		IsShaffle = false;
	}
	else
	{
		if (QHand != nullptr)
		{
			WHand = UnusedDeck.front();
		}
		else
		{
			QHand = UnusedDeck.front();

		}
	}

	UnusedDeck.pop_front();
}


void CDeck::SetOwner(CGameObject* _Object)
{
	Owner = _Object;
	OwnerScript = Owner->GetScript<CFieldObjScript>();
}

void CDeck::AddMagic(CMagic* Magic)
{
	MagicList.push_back(Magic);
}


void CDeck::CastFirst()
{
	if (!(OwnerScript->GetStatus().Current_MP < QHand->GetMagicInfo().ManaCost))
	{
		OwnerScript->UseMana(QHand->GetMagicInfo().ManaCost);
		QHand->SetCaster(Owner);
		QHand->cast(OwnerScript->GetOwnerIdx());

		Grave.push_back(QHand);
		QHand = nullptr;
		FillHand();
	}

}

void CDeck::CastSecond()
{
	if (!(OwnerScript->GetStatus().Current_MP < WHand->GetMagicInfo().ManaCost))
	{
		OwnerScript->UseMana(WHand->GetMagicInfo().ManaCost);
		WHand->SetCaster(Owner);
		WHand->cast(OwnerScript->GetOwnerIdx());

		Grave.push_back(WHand);
		WHand = nullptr;
		FillHand();
	}
}

void CDeck::Shuffle()
{
	deque<CMagic*> Generator = MagicList;


	for(int i =0; i < MagicList.size(); ++i)
	{
		int idx = CRandomMgr::GetInst()->GetRandom(Generator.size());

		UnusedDeck.push_back(Generator[idx]);

		Generator.erase(Generator.begin() + idx);
	}

	Grave.clear();
	
}
