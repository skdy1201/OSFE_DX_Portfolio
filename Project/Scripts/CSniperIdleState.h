#pragma once

#include  <Engine/CState.h>

#include <Engine/CGameObject.h>
#include "CFieldObjScript.h"

class CSniperIdleState :
	public CState
{
private:
	CGameObject*			Player;
	CFieldObjScript*		PlayerScript;

	CFieldObjScript*		SniperScript;

	float*					MoveTimer;
	float*					AttackTimer;

public:
	virtual void finaltick() override;
	virtual void Enter() override;
	virtual void Exit() override;

public:
	CSniperIdleState();
	~CSniperIdleState();
};

