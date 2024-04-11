#include "pch.h"
#include "CDeck.h"

#include <Engine/CGameObject.h>

#include "CFieldObjScript.h"
#include "CMagic.h"
#include "CRandomMgr.h"

CDeck::CDeck()
	: IsShaffle(false)
	, UseQHand(false)
	, UseWHand(false)
	,ShuffleTimer(3.f)
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
	}



	if(IsShaffle == true && ShuffleTimer <= 0.f)
	{
		Shuffle();

		QHand = UnusedDeck.front();
		UnusedDeck.pop_front();

		WHand = UnusedDeck.front();
		UnusedDeck.pop_front();

		IsShaffle = false;
		ShuffleTimer = 3.f;
		
	}

	if (IsShaffle == false && UnusedDeck.size() > 0)
	{
		if (QHand != nullptr && WHand == nullptr)
		{
			WHand = UnusedDeck.front();
			UnusedDeck.pop_front();
		}
		else if(QHand == nullptr)
		{
			QHand = UnusedDeck.front();
			UnusedDeck.pop_front();
		}
	}

	
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
	if (QHand == nullptr)
		return;

	if (!(OwnerScript->GetStatus().Current_MP < QHand->GetMagicInfo().ManaCost))
	{
		OwnerScript->UseMana(QHand->GetMagicInfo().ManaCost);
		QHand->SetCaster(Owner);
		QHand->cast(OwnerScript->GetOwnerIdx());

		Grave.push_back(QHand->GetMagicIcon());
		QHand = nullptr;
		FillHand();

		SetUseQHand(true);
	}

}

void CDeck::CastSecond()
{
	if (WHand == nullptr)
		return;

	if (!(OwnerScript->GetStatus().Current_MP < WHand->GetMagicInfo().ManaCost))
	{
		OwnerScript->UseMana(WHand->GetMagicInfo().ManaCost);
		WHand->SetCaster(Owner);
		WHand->cast(OwnerScript->GetOwnerIdx());

		Grave.push_back(WHand->GetMagicIcon());
		WHand = nullptr;
		FillHand();

		SetUseWHand(true);

	}
}

void CDeck::MoveToGrave()
{
	
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
