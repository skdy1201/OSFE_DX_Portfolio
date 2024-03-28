#pragma once
#include "CRenderComponent.h"
class CMeshRender :
    public CRenderComponent
{
public:
    bool        RenderPossible;

    void SetRenderPossible(bool _Change) { RenderPossible = _Change; }

    virtual void UpdateData() override;
    virtual void finaltick() override;
    virtual void render() override;
     
    CLONE(CMeshRender);
public:
    CMeshRender();
    ~CMeshRender();
};

