#pragma once

#include <Engine/CState.h>

class CFieldObjScript;
class CTerraScript;
class CGameObject;

class CTerraHitState :
    public CState
{
	CGameObject* Terra;
	CTerraScript* TerraScript;

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
	CTerraHitState();
	~CTerraHitState();

};

