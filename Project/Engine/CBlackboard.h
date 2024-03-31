#pragma once
#include "CEntity.h"

enum class BB_DATA
{
    INT,
    FLOAT,
    VEC2,
    VEC3,
    VEC4,
    OBJECT,
};

struct tBlackboardData
{
    BB_DATA     Type;
    void*       pData;
};

class CBlackboard :
    public CEntity
{
private:
    map<wstring, tBlackboardData>   m_mapBBData;


public:
    void AddBlackboardData(const wstring& _strKey, BB_DATA _Type, void* _Data);
    void* GetBlackboardData(const wstring& _strKey);

    void Save(ofstream& _fout);
    void Load(ifstream& _fin);

    static void (*SaveGameObject)(class CGameObject* _Obj, ofstream& _fout);
    static class CGameObject* (*LoadGameObject)(ifstream& _fin);


    CLONE(CBlackboard);
public:
    CBlackboard();
    CBlackboard(const CBlackboard& _board);
    ~CBlackboard();

    friend class StateMachineUI;
};

