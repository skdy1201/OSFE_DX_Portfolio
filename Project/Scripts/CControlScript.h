#pragma once

#include <Engine/CScript.h>

class CControlScript :
    public CScript
{
private:

    CGameObject* m_Owner;

public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(ofstream& _File) override;
    virtual void LoadFromFile(ifstream& _File) override;
    CLONE(CControlScript);
public:
    CControlScript();
    ~CControlScript();
};

