#pragma once

#include <Engine/CScript.h>

#include "CFieldObjScript.h"

class CFieldObjScript;

class CSniperScript :
    public CFieldObjScript
{
private:
    float            m_MoveCooltime;
    int              CurRow;
    int             MoveDir; // 1 :: down, 2 :: up
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

