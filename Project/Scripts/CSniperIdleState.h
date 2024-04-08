#pragma once

#include  <Engine/CState.h>


class CSniperScript;
class CFieldObjScript;

class CSniperIdleState :
	public CState
{
private:
	CGameObject*			Player;
	CFieldObjScript*		PlayerScript;

	CGameObject*			Owner;
	CSniperScript*			OwnerScript;


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

