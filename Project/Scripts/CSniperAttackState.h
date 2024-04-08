#pragma once

#include <Engine/CState.h>

class CFieldObjScript;

class CSniperAttackState :
    public CState
{
	CGameObject* Sniper;
	CFieldObjScript* OwnerScript;
	CGameObject* AnimatorObject;

	Ptr<CPrefab> SniperShoot;


	float*		AttackTimer;
	float*		MoveTimer;

public:

	virtual void finaltick() override;
	virtual void Enter() override;
	virtual void Exit() override;

public:
	CSniperAttackState();
	~CSniperAttackState();
};

