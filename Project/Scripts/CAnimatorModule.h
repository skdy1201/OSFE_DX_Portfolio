#pragma once

#include <Engine/CScript.h>

class CAnimatorModule :
    public CScript
{
protected:
    CGameObject* pObj;
    CAnimator2D* OwnerAnimator;

    wstring     AnimName;
    int         count;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(ofstream& _File) override;
    virtual void LoadFromFile(ifstream& _File) override;
    CLONE(CAnimatorModule);
public:
    CAnimatorModule();
    CAnimatorModule(UINT type);
    ~CAnimatorModule();
};

