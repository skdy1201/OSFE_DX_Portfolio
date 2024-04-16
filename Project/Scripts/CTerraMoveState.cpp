#include "pch.h"
#include "CTerraMoveState.h"

#include <Engine/CStateMachine.h>
#include <Engine/CCollider2D.h>

#include "CFieldScript.h"
#include "CFieldObjScript.h"
#include "CTerraScript.h"
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
	TerraScript = this->GetFSM()->GetStateMachine()->GetOwner()->GetScript<CTerraScript>();
	MoveCooldtime = (float*)GetBlackboardData(L"MoveCooldown");



	if(TerraScript->GetMovedByAttack() == false)
	{
		this->GetFSM()->GetStateMachine()->GetOwner()->Collider2D()->SetOffsetScale(Vec2(0.f, 0.f));

		CurField = this->GetFSM()->GetStateMachine()->GetOwner()->GetScript<CFieldObjScript>()->GetField();


		MoveTime = CRandomMgr::GetInst()->GetRandom(4);
		MoveTime += 8;

		for(int i = 0; i < MoveTime; ++i)
		{
			int newCol = CRandomMgr::GetInst()->GetRandom(4);
			newCol += 8;

			int newRow = CRandomMgr::GetInst()->GetRandom(4);

			MoveIdxList.push(Vec2(newCol, newRow));
		}

		MoveComplete = true;
	}
}

void CTerraMoveState::finaltick()
{
	if (TerraScript->GetMovedByAttack())
	{
		TerraScript->MovedByAttack();

		if (TerraScript->GetOwnerIdx() == Vec2(TerraScript->GetOwnerIdx().x + TerraScript->GetMovedIdx().x, TerraScript->GetOwnerIdx().y + TerraScript->GetMovedIdx().y))
		{

			*MoveCooldtime = 0.f;

			ChangeState(L"CTerraIdleState");

		}
	}
	else
	{
		if (MoveComplete == true)
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


		if (xlength > 1.f && ylength > 1.f)
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


		if (MoveIdxList.size() == 0 && MoveComplete == true)
		{
			ChangeState(L"CTerraIdleState");
		}
	}


}

void CTerraMoveState::Exit()
{
	this->GetFSM()->GetStateMachine()->GetOwner()->Collider2D()->SetOffsetScale(Vec2(40.f, 40.f));

	*MoveCooldtime = 0.f;
}
