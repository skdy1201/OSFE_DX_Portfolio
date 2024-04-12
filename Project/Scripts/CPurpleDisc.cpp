#include "pch.h"
#include "CPurpleDisc.h"

#include "CFieldScript.h"
#include "CRandomMgr.h"

CPurpleDisc::CPurpleDisc()
{


}

CPurpleDisc::CPurpleDisc(const CPurpleDisc& _Origin)
{
}

CPurpleDisc::~CPurpleDisc()
{
}

void CPurpleDisc::begin()
{
	Dir[0] = Vec2(0, 1);
	Dir[1] = Vec2(0, -1);
	Dir[2] = Vec2(-1, 0);
	Dir[3] = Vec2(1, 0);

	Colignore = 1;

	// 정보 세팅
	Proj_Struct Info = this->GetInfo();

	Info.Damage = 50;
	Info.MaxRange = 4;
	Info.LifeCount = -1;
	Info.LifeTime = 6.f;
	Info.TargetTile = false;
	Info.m_Speed = 500.f;

	this->SetInfo(Info);

	ResetDir();

	Animator2D()->Play(PurpleDisc, true);
}

void CPurpleDisc::tick()
{
	Move(DT);

	if ((Transform()->GetRelativePos().x < - 470.f || Transform()->GetRelativePos().x > 20.f)
		|| (Transform()->GetRelativePos().y < -250.f || Transform()->GetRelativePos().y > 80.f))
	{
		this->GetOwner()->Destroy();
	}
	
}

void CPurpleDisc::ResetDir()
{
	vector<Vec2> PossibleDir;

	for (int i = 0; i < 4; ++i)
	{
		Vec2 NextFieldIdx = {};
		NextFieldIdx = StartIndex + Dir[i];

		if(NextFieldIdx.x > 3 && NextFieldIdx.x < 8 &&
			NextFieldIdx.y > -1 && NextFieldIdx.y < 4)
		{
			PossibleDir.push_back(Dir[i]);
		}
	}

	if(PossibleDir.size() > 0)
	{
		int Random = CRandomMgr::GetInst()->GetRandom(PossibleDir.size());
		CurDir = PossibleDir[Random];
		CalculateDir(StartIndex, PossibleDir[Random]);
	}
}

void CPurpleDisc::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (Colignore == 1)
		--Colignore;
	else
	{
		this->StartIndex += CurDir;

		
	}
}

void CPurpleDisc::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	Vec3 Pos = _OtherObj->Transform()->GetRelativePos();

	Pos -= this->Transform()->GetRelativePos();
	if(abs(Pos.x) < 1.f && abs(Pos.y) < 1.f && abs(Pos.z) < 1.f )
	{
		if (StartIndex.x <= 4 || StartIndex.x >= 7
			|| StartIndex.y <= 0 || StartIndex.y >= 3)
		{
			Vec3 CurPos = m_CurField->GetTilePosition(StartIndex);
			this->Transform()->SetRelativePos(CurPos);
			ResetDir();
		}
	}

	
}

void CPurpleDisc::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CProjectileScript::EndOverlap(_Collider, _OtherObj, _OtherCollider);
}