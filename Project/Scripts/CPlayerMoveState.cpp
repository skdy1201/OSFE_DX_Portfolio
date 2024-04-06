#include "pch.h"
#include "CPlayerMoveState.h"

#include <Engine/CTimeMgr.h>

#include  "CFieldObjScript.h"

#include <Engine/CAnimator2D.h>
#include <Engine/CAnim.h>

#include "CFieldScript.h"

CPlayerMoveState::CPlayerMoveState()
	: CState((UINT)STATE_TYPE::PLAYERMOVESTATE)
	, Player(nullptr)
	, PlayerScript(nullptr)
	, MovingTime(0.f)
{
}

CPlayerMoveState::~CPlayerMoveState()
{
}

void CPlayerMoveState::Enter()
{
	Player = BlackBoardPlayer;
	PlayerScript = Player->GetScript<CFieldObjScript>();
	Field = PlayerScript->GetField();

	NextIdx = *(Vec2*)GetBlackboardData(L"NextIdx");
	MoveIdx = PlayerScript->GetOwnerIdx() + NextIdx;
	TargetPos = Field->GetNextTilePos(Player, MoveIdx, PlayerZ);
	if(Player->Transform()->GetRelativePos() == TargetPos)
	{
		ChangeState(L"CPlayerIdleState");
	}


	Vector3 Dis = {};

	Distance = Dis.Distance(Player->Transform()->GetRelativePos(), TargetPos);

	MovingTime = 0.1f;
	Speed = Distance / MovingTime;
}

void CPlayerMoveState::finaltick()
{
	Vec3 PlayerPos = Player->Transform()->GetRelativePos();

	if(MovingTime <= 0.f)
	{
		Player->Transform()->SetRelativePos(TargetPos);
		PlayerScript->SetOwnerIdx(MoveIdx);

		ChangeState(L"CPlayerIdleState");
		return;
	}

	Vec2 dir = NextIdx;
	dir.Normalize();
	PlayerPos.x += dir.x * Speed * DT;
	PlayerPos.y += dir.y * Speed * DT;

	Player->Transform()->SetRelativePos(PlayerPos);
	MovingTime -= DT;

}

void CPlayerMoveState::Exit()
{
	
}
