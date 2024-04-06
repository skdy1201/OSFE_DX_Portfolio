#pragma once

#include <Engine/CState.h>

class CGameObject;
class CFieldObjectScript;


class CPlayerEntryState :
    public CState
{
    CGameObject*        Player;
    CFieldObjectScript* PlayerScript;

public:

    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
	CPlayerEntryState();
	~CPlayerEntryState();
};

