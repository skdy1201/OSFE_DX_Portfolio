#pragma once

#include "CUIScript.h"


class CFieldObjScript;
class CDeck;
class MagicManager;

class CDeckCoverUI :
    public CUIScript
{
private:

    CGameObject*        Player;
    CFieldObjScript*    PlayerScript;
    CDeck*              PlayerDeck;

	Vec2                IconOffset;

    vector<CGameObject*> IconObjvector;
    bool                 FirstSet;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(ofstream& _File) override;
    virtual void LoadFromFile(ifstream& _File) override;
    CLONE(CDeckCoverUI);
public:
    CDeckCoverUI();
    ~CDeckCoverUI();
};

