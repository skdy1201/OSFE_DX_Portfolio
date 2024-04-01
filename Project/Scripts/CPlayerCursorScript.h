#pragma once

#include <Engine/CScript.h>script

class CFieldScript;
class CFieldObjScript;


class CPlayerCursorScript :
    public CScript
{
private:

    CFieldObjScript*    m_PlayerScript;
    CFieldScript*       m_Field;
    Vec2                AttackRange;
    Vec2                CurIndex;

public:
    void SetIndex(Vec2 _Index) { CurIndex = _Index; }
    Vec2 GetIndex() { return CurIndex; }

    void SetField(CFieldScript* _Field) { m_Field = _Field; }
    CFieldScript* GetField() { return m_Field; }

    void SetPlayerScript(CFieldObjScript* PlayerScript) { m_PlayerScript = PlayerScript; }


    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(ofstream& _File) override;
    virtual void LoadFromFile(ifstream& _File) override;

public:
    CLONE(CPlayerCursorScript);
    CPlayerCursorScript();
    CPlayerCursorScript(const CPlayerCursorScript& _Origin);
    ~CPlayerCursorScript();
};


