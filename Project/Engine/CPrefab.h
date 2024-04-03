#pragma once
#include "CAsset.h"
#include "CGameObject.h"

typedef void(*SAVE_TYPE)(CGameObject*, ofstream&);
typedef CGameObject* (*LOAD_TYPE)(ifstream&);

class CPrefab :
    public CAsset
{
public:
    static SAVE_TYPE GAMEOBJECT_SAVE;
    static LOAD_TYPE GAMEOBJECT_LOAD;

private:
    CGameObject*    m_ProtoObj;

public:
    void SetGameObject(CGameObject* _Object);
    CGameObject* Instantiate();
    int GetPrefabIndex() { return m_ProtoObj->GetLayerIdx(); }

    static CGameObject* GetPrefabObj(wstring NameKey);


    CLONE_DISABLE(CPrefab);
public:
    virtual int Save(const wstring& _strRelativePath);
    virtual int Load(const wstring& _strFilePath);

public:
    CPrefab(bool _Engine = false);
    CPrefab(CGameObject* _Proto, bool _Engine);
    ~CPrefab();
};

