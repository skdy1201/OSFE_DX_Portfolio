#include "pch.h"
#include "CTerraMoveState.h"

#include <Engine/CStateMachine.h>

#include "CFieldScript.h"
#include "CFieldObjScript.h"
#include "CRandomMgr.h"

CTerraMoveState::CTerraMoveState()
	: CState((UINT)STATE_TYPE::TERRAMOVESTATE)
{
}

CTerraMoveState::~CTerraMoveState()
{
}

void CTerraMoveState::Enter()
{
	TerraScript = this->GetFSM()->GetStateMachine()->GetOwner()->GetScript<CFieldObjScript>();

	MoveCooldtime = (float*)GetBlackboardData(L"MoveCooldown");
	CurField = this->GetFSM()->GetStateMachine()->GetOwner()->GetScript<CFieldObjScript>()->GetField();


	MoveTime = CRandomMgr::GetInst()->GetRandom(4);
	MoveTime += 5;

	for(int i = 0; i < MoveTime; ++i)
	{
		int newCol = CRandomMgr::GetInst()->GetRandom(4);
		newCol += 8;

		int newRow = CRandomMgr::GetInst()->GetRandom(4);

		MoveIdxList.push(Vec2(newCol, newRow));
	}

	MoveComplete = true;
}

void CTerraMoveState::finaltick()
{
	if(MoveComplete == true)
	{
		TargetIdx = MoveIdxList.front();
		MoveIdxList.pop();

		TargetTilePos = CurField->GetTilePosition(TargetIdx);
		MoveComplete = false;

		this->GetFSM()->GetStateMachine()->GetOwner()->Animator2D()->Play(L"TerraMove");
	}

		Vec3 CurPos = this->GetFSM()->GetStateMachine()->Transform()->GetRelativePos();

		Vec3 Dir = TargetTilePos - CurPos;
		float distance = Dir.Length();

		float xlength = abs(Dir.x);
		float ylength = abs(Dir.y);

		Dir.Normalize();


		if(xlength > 1.f && ylength > 1.f)
		{
			CurPos += Dir * 750.f * DT;
			this->GetFSM()->GetStateMachine()->Transform()->SetRelativePos(CurPos);

		}
		else
		{
			this->GetFSM()->GetStateMachine()->Transform()->SetRelativePos(TargetTilePos);
			TerraScript->SetOwnerIdx(TargetIdx);
			MoveComplete = true;

		}


	if(MoveIdxList.size() == 0 && MoveComplete == true)
	{
		ChangeState(L"CTerraIdleState");
	}
}

void CTerraMoveState::Exit()
{
		*MoveCooldtime = 0.f;
}
