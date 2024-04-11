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
    vector<CGameObject*> Grave;

    CFieldObjScript* OwnerScript;


    bool    IsShaffle;
    bool    UseQHand;
    bool    UseWHand;

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

    bool GetUseQHand() { return UseQHand; }
    bool GetUseWHand() { return UseWHand; }
    bool GetIsShuffle() { return IsShaffle; }

    void SetUseQHand(bool fact) { UseQHand = fact; }
    void SetUseWHand(bool fact) { UseWHand = fact; }
    void SetIsShuffle(bool fact) { IsShaffle = fact; }

    vector<CGameObject*> GetGrave() { return Grave; }

    void MoveToGrave();


    CLONE(CDeck);
public:
    CDeck();
    ~CDeck();
};

