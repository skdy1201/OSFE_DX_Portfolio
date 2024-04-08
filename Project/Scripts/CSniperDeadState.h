#pragma once

#include <Engine/CState.h>

class CSniperDeadState :
    public CState
{
private:
    CGameObject* Owner;

public:
	virtual void finaltick() override;
	virtual void Enter() override;
	virtual void Exit() override;

public:
	CSniperDeadState();
	~CSniperDeadState();
};

