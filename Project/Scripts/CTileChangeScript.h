#pragma once
#include <Engine/CScript.h>
#include <Engine/components.h>


class CTileChangeScript :
    public CScript
{
private :
    int               CurTexIdx;
    Ptr<CMaterial>    TileMtrl;

    bool              Ischange;
    tScriptParam      ColorParam;


public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(ofstream& _File);
    virtual void LoadFromFile(ifstream& _File);
    CLONE(CTileChangeScript);
public:
    CTileChangeScript();
    CTileChangeScript(const CTileChangeScript& _Origin);
    ~CTileChangeScript();
};

