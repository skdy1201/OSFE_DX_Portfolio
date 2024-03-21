#pragma once
#include "AssetUI.h"

class MaterialUI :
    public AssetUI
{
private:
    TEX_PARAM       m_SelectTexParam;
    bool            m_CheckMaterial[10];

    //이전 재질과 지금 재질을 비교
    Ptr<CMaterial> currentMtrl;
    Ptr<CMaterial> prevMtrl;

public:
    virtual void render_update() override;
    void make_Textable(bool* _texarr, Ptr<CMaterial>& pMtrl);
    void AddTexture(Ptr<CMaterial> _mtrl, TEX_PARAM _Param, wstring Key, string paramname, bool* _arr, UINT barrnum);


public:
    void SelectTexture(DWORD_PTR _dwData);

public:
    MaterialUI();
    ~MaterialUI();
};
