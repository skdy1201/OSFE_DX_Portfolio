#pragma once

#include <Engine/CState.h>

class CPlayerDeadState :
    public CState
{
	CGameObject* Owner;

	int  animcount;

public:
	virtual void finaltick() override;
	virtual void Enter() override;
	virtual void Exit() override;

public:
	CPlayerDeadState();
	~CPlayerDeadState();
};

