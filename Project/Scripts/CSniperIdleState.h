#pragma once

#include  <Engine/CState.h>


class CFieldObjScript;

class CSniperIdleState :
	public CState
{
private:
	CGameObject*			Player;
	CFieldObjScript*		PlayerScript;

	CGameObject*			Owner;
	CFieldObjScript*		OwnerScript;

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

