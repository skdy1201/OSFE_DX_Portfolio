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
    bool    UseHand;

public:
    void begin();

    void FillHand();

	void SetOwner(CGameObject* _Object);

    void AddMagic(CMagic* Magic);

    void CastFirst();
    void CastSecond();

    void Shuffle();

    deque<CMagic*> GetMagicList() { return MagicList; }
    deque<CMagic*> GetUnusedDeck() { return UnusedDeck; }

    CMagic* GetQHand() { return QHand; }
    CMagic* GetWHand() { return WHand; }

    bool GetUseHand() { return UseHand; }
    bool GetIsShuffle() { return IsShaffle; }

    void SetUseHand(bool fact) { UseHand = fact; }
    void SetIsShuffle(bool fact) { IsShaffle = fact; }


    CLONE(CDeck);
public:
    CDeck();
    ~CDeck();
};

