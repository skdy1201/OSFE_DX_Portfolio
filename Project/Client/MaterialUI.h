#pragma once
#include "AssetUI.h"

class MaterialUI :
    public AssetUI
{
private:
    TEX_PARAM       m_SelectTexParam;
    bool            m_CheckMaterial[10];

public:
    virtual void render_update() override;
    void make_Textable(bool* _texarr, Ptr<CMaterial> pMtrl);



public:
    void SelectTexture(DWORD_PTR _dwData);

public:
    MaterialUI();
    ~MaterialUI();
};

