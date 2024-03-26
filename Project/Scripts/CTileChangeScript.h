#pragma once
#include <Engine/CScript.h>
#include <Engine/components.h>

#include "CPlayerScript.h"

class CTileChangeScript :
    public CScript
{
private :
    int               CurTexIdx;
    int               PrevTexIdx;
    Ptr<CMaterial>    TileMtrl;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(ofstream& _File);
    virtual void LoadFromFile(ifstream& _File);
    CLONE(CTileChangeScript);
public:
    CTileChangeScript();
    ~CTileChangeScript();
};

