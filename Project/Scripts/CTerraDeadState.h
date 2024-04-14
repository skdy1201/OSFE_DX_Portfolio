#pragma once

#include <Engine/CState.h>

class CTerraDeadState :
    public CState
{
private:
	CGameObject* Owner;

	int  animcount;

public:
	virtual void finaltick() override;
	virtual void Enter() override;
	virtual void Exit() override;

public:
	CTerraDeadState();
	~CTerraDeadState();
};

