#pragma once

#include <Engine/CState.h>

class CFieldObjScript;
class CSniperScript;
class CGameObject;

class CSniperHitState :
    public CState
{
	CGameObject* Sniper;
	CSniperScript* SniperScript;

	int CurRow;
	int PlayerRow;

	CGameObject* Player;
	CFieldObjScript* PlayerScript;

	CGameObject* HitFX;

	float* AttackTimer;
	float* MoveTimer;

public:

	virtual void finaltick() override;
	virtual void Enter() override;
	virtual void Exit() override;

public:
	CSniperHitState();
	~CSniperHitState();
};

