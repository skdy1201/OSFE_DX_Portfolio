#pragma once

#include <Engine/CScript.h>

class CFieldScript;

struct Health
{
	CGameObject*	Owner;
	int				HP;
	int				MP;

	int				Current_HP;
	int				Current_MP;

	int				SpellPower; // 주문력

	int				Defense; // 방어력
	int				Shield; // 쉴드

	int				Level;
	int				Exp;
	int				RewardExp; // 처치시 경험치

	int				Camp; // 진영
};

class CFieldObjScript :
    public CScript
{
private:
	Health	m_Health;

	CGameObject*		m_Owner;
	CFieldScript*		m_Field;
	bool				IsPlayer;


public:
	Health& GetHealth() { return m_Health; }
	void Move();


	void SetField(CFieldScript* _Field) { m_Field = _Field; }

	virtual void begin() override;
	virtual void tick() override;

	virtual void SaveToFile(ofstream& _File) override;
	virtual void LoadFromFile(ifstream& _File) override;

public:
	CLONE(CFieldObjScript);
	CFieldObjScript();
	CFieldObjScript(const CFieldObjScript& _Origin);
	~CFieldObjScript();
};

