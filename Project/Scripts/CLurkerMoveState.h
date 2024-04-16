#pragma once

#include <Engine/CState.h>

class CLurkerScript;

class CLurkerMoveState :
    public CState
{
	CGameObject*		Lurker;
	CLurkerScript*		OwnerScript;
	Vec2                m_OwnerIdx;

	float* Attackcooltime;



public:

	virtual void finaltick() override;
	virtual void Enter() override;
	virtual void Exit() override;

public:
	CLurkerMoveState();
	~CLurkerMoveState();
};

