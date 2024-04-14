#include "pch.h"
#include "CPurpleDisc.h"

#include "CFieldScript.h"
#include "CRandomMgr.h"
#include "CTileScript.h"

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
	Info.LifeTime = 3.5f;
	Info.TargetTile = false;
	Info.m_Speed = 650.f;

	this->SetInfo(Info);

	ResetDir();

	Animator2D()->Play(PurpleDisc, true);
}

void CPurpleDisc::tick()
{
	Move(DT);


	m_ProjInfo.LifeTime -= DT;

	if (m_ProjInfo.LifeTime <= 0.f)
		GamePlayStatic::DestroyGameObject(this->GetOwner());
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
		StartIndex += CurDir;
	}
}

void CPurpleDisc::Calculate_Disc_Dir()
{
	if (once)
		return;

	// 오브젝트 방향 가져오기
	Vec3 vecObjDir = this->Transform()->GetWorldDir(DIR_TYPE::RIGHT);
	Vec3 vecTilePos = m_CurField->GetTilePosition(StartIndex);
	Vec3 vecObjPos = this->Transform()->GetRelativePos();
	// 위
	if (vecObjDir.y == 1)
	{
		// 만약 목표한 타일보다 오브젝트가 더 위로 갔다면,
		if (vecTilePos.y - vecObjPos.y >= 0)
		{
			this->Transform()->SetRelativePos(Vec3(vecTilePos.x, vecTilePos.y, vecObjPos.z));
			ResetDir();
			once = true;
		}
	}
	// 아래
	else if (vecObjDir.y == -1)
	{
		// 만약 목표한 타일보다 오브젝트가 더 아래로 갔다면,
		if (vecTilePos.y - vecObjPos.y <= 0)
		{
			this->Transform()->SetRelativePos(Vec3(vecTilePos.x, vecTilePos.y, vecObjPos.z));
			ResetDir();
			once = true;
		}
	}
	// 왼
	else if (vecObjDir.x == -1)
	{
		// 만약 목표한 타일보다 오브젝트가 더 완쪽으로 갔다면,
		if (vecTilePos.x - vecObjPos.x >= 0)
		{
			this->Transform()->SetRelativePos(Vec3(vecTilePos.x, vecTilePos.y, vecObjPos.z));
			ResetDir();
			once = true;
		}
	}
	// 오
	else if (vecObjDir.x == 1)
	{
		// 만약 목표한 타일보다 오브젝트가 더 오른쪽으로 갔다면,
		if (vecTilePos.x - vecObjPos.x <= 0)
		{
			this->Transform()->SetRelativePos(Vec3(vecTilePos.x, vecTilePos.y, vecObjPos.z));
			ResetDir();
			once = true;
		}
	}
}

void CPurpleDisc::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if(_OtherObj->GetScript<CTileScript>())
	{
		if (Colignore == 1)
			--Colignore;
	}
	else
	{
		_OtherObj->GetScript<CFieldObjScript>()->Hit(this->GetInfo().Damage);
	}
}

void CPurpleDisc::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	Calculate_Disc_Dir();
}

void CPurpleDisc::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CProjectileScript::EndOverlap(_Collider, _OtherObj, _OtherCollider);

	once = false;
}