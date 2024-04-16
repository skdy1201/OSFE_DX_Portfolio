#pragma once

#include <Engine/CState.h>

class CFieldObjScript;
class CLurkerScript;
class CGameObject;

class CLurkerHitState :
    public CState
{
	CGameObject* Lurker;
	CLurkerScript* LurkerScript;

	CGameObject* Player;
	CFieldObjScript* PlayerScript;

	CGameObject* HitFX;

	float* AttackTimer;

public:

	virtual void finaltick() override;
	virtual void Enter() override;
	virtual void Exit() override;

public:
	CLurkerHitState();
	~CLurkerHitState();
};

