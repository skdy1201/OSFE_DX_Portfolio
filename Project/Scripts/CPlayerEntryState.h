#pragma once

#include <Engine/CState.h>

class CGameObject;
class CFieldObjScript;


class CPlayerEntryState :
    public CState
{
    CGameObject*        Player;
    CFieldObjScript* PlayerScript;

public:

    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
	CPlayerEntryState();
	~CPlayerEntryState();
};

