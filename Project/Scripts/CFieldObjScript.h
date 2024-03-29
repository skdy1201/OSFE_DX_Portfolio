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

	int				SpellPower; // �ֹ���

	int				Defense; // ����
	int				Shield; // ����

	int				Level;
	int				Exp;
	int				RewardExp; // óġ�� ����ġ

	int				Camp; // ����
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

