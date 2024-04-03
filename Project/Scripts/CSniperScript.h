#pragma once

#include <Engine/CScript.h>

class CFieldObjScript;

class CSniperScript :
    public CScript
{
private:
    float            m_MoveCooltime;
    int              CurRow;

    CFieldObjScript* OwnerFojScript;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(ofstream& _File) override;
    virtual void LoadFromFile(ifstream& _File) override;
    CLONE(CSniperScript);
public:
    CSniperScript();
    ~CSniperScript();

};

