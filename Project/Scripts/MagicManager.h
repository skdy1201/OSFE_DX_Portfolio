#pragma once

#include<Engine/CEntity.h>

class MagicManager :
    public CEntity
{
private:

    vector<CGameObject*> iconlist;

    CLONE_DISABLE(MagicManager);

public:
    vector<CGameObject*> GetMagicIconList() { return iconlist; }

public:
    MagicManager();
    ~MagicManager() override;

};

