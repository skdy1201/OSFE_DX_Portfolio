#include "pch.h"
#include "CDeck.h"

#include <Engine/CGameObject.h>

#include "CFieldObjScript.h"
#include "CMagic.h"
#include "CRandomMgr.h"

CDeck::CDeck()
{
}

CDeck::~CDeck()
{
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
	if(UnusedDeck.size() == 0)
	{
		Shuffle();
	}

	if(QHand != nullptr)
	{
		WHand = UnusedDeck.front();
	}

	QHand = UnusedDeck.front();

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
}
