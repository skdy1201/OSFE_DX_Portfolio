#pragma once

#include <deque>

class CFieldObjScript;
class CMagic;

class CDeck 
{
private:

    CGameObject* Owner;
    
    deque<CMagic*> MagicList;
    deque<CMagic*> UnusedDeck;

    CMagic* QHand;
    CMagic* WHand;
    list<CMagic*> Grave;

    CFieldObjScript* OwnerScript;

    bool    IsShaffle;

public:
    void begin();

    void FillHand();

	void SetOwner(CGameObject* _Object);

    void AddMagic(CMagic* Magic);

    void CastFirst();
    void CastSecond();

    void Shuffle();


    CLONE(CDeck);
public:
    CDeck();
    ~CDeck();
};

