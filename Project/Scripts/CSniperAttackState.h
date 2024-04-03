#pragma once

#include <Engine/CAnim.h>
#include <Engine/CState.h>

class CSniperAttackState :
    public CState
{
	CGameObject* Sniper;
	CGameObject* AnimatorObject;

	Ptr<CPrefab> SniperShoot;

public:

	virtual void finaltick() override;
	virtual void Enter() override;
	virtual void Exit() override;

public:
	CSniperAttackState();
	~CSniperAttackState();
};

