#pragma once
#include <Engine/CScript.h>

class CCameraMoveScript :
    public CScript
{
private:
    float       m_CamSpeed;

public:
    virtual void tick();

private:
    void MoveOrthographic();
    void MovePerspective();

    virtual void SaveToFile(ofstream& _File) override {};
    virtual void LoadFromFile(ifstream& _File) override {};
    CLONE(CCameraMoveScript);
public:
    CCameraMoveScript();
    ~CCameraMoveScript();
};

