#pragma once

#include <Engine/CState.h>

class CLurkerDeadState :
    public CState
{
private:
	CGameObject* Owner;

public:
	virtual void finaltick() override;
	virtual void Enter() override;
	virtual void Exit() override;

public:
	CLurkerDeadState();
	~CLurkerDeadState();
};

