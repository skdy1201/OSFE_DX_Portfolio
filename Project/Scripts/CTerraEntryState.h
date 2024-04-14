#pragma once

class CFieldObjScript;

class CTerraEntryState :
    public CState
{
    CGameObject* Terra;
    CFieldObjScript* TerraFieldScript;

public:

    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CTerraEntryState();
    ~CTerraEntryState();
};

