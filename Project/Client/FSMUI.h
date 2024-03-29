#pragma once
#include "AssetUI.h"

class FSMUI :
    public AssetUI
{

private:
    char m_NameBuff[32];
    Ptr<CFSM> m_target;
    vector<string> m_vecNames;
public:
    virtual void render_update() override;
    virtual void Activate() override;


private:
    void Save();
    void StateList();
    void AddState();

public:
    FSMUI();
    ~FSMUI();
};

