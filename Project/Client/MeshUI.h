#pragma once
#include "AssetUI.h"

class MeshUI :
    public AssetUI
{
private:

    Ptr<CMesh> TargetMesh;

public:
    virtual void render_update() override;

public:
    MeshUI();
    ~MeshUI();
};

