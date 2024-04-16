#pragma once

#include <Engine/CState.h>

class CFieldScript;
class CFieldObjScript;
class CLurkerScript;

class CLurkerAttackState
	: public CState
{
	CGameObject* Lurker;
	CLurkerScript* OwnerScript;
	CFieldScript* field;
	CGameObject* AnimatorObject;

	CFieldObjScript* PlayerScript;

	Ptr<CPrefab> LurkerShot;
	Ptr<CPrefab> Warning;

	float* AttackTimer;
	int SpawnCOUNT;

public:

	virtual void finaltick() override;
	virtual void Enter() override;
	virtual void Exit() override;

public:
	CLurkerAttackState();
	~CLurkerAttackState();
};

