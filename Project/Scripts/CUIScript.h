#pragma once

#include <Engine/CScript.h>

class CUIScript :
    public CScript
{
protected:

    CGameObject* pObj;

    Vec3 FirstPos;
    Vec3 FirstScale;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(ofstream& _File) override;
    virtual void LoadFromFile(ifstream& _File) override;
    CLONE(CUIScript);
public:
    CUIScript();
    CUIScript(UINT _int);
    ~CUIScript();
};

