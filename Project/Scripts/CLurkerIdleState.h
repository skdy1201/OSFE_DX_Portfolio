#pragma once

#include <Engine/CState.h>

class CLurkerScript;
class CFieldObjScript;

class CLurkerIdleState :
    public CState
{
private:

	CGameObject* Player;
	CFieldObjScript* PlayerScript;

	CGameObject* Owner;
	CLurkerScript* OwnerScript;


	float* AttackTimer;

public:
	virtual void finaltick() override;
	virtual void Enter() override;
	virtual void Exit() override;

public:
	CLurkerIdleState();
	~CLurkerIdleState();
};

