#pragma once
#include "AssetUI.h"

class MaterialUI :
    public AssetUI
{
private:
    TEX_PARAM       m_SelectTexParam;

    bool            m_CheckMaterial[10];

    bool            m_CheckScalar[(int)SCALAR_PARAM::END];
    vector<int>     m_inscalarparamnum;
    char            newscalarparam[128];

    bool            m_IsChange;

	char     inputParam[(int)TEX_PARAM::TEX_5][128];

    //이전 재질과 지금 재질을 비교
    Ptr<CMaterial> currentMtrl;
    Ptr<CMaterial> prevMtrl;

public:
    virtual void render_update() override;
    void make_Textable(bool* _texarr, Ptr<CMaterial>& pMtrl);
    void make_Scalartable(bool* _scalararr, Ptr<CMaterial>& pMtrl);
    void Check_ChangeDesc(Ptr<CMaterial>& _Curmtrl, TEX_PARAM _CurrentTexParam, string _ChangeDesc);
    void ShaderSelect(DWORD_PTR _ptr);


public:
    void SelectTexture(DWORD_PTR _dwData);

public:
    MaterialUI();
    ~MaterialUI();
};
