#pragma once

#include <Engine/CScript.h>

class CDeck;
class CMagic;

class CFieldScript;

struct Status
{
	CGameObject* Owner;
	int HP;
	float MP;

	int Current_HP;
	float Current_MP;

	float Mana_Regen;

	int SpellPower; // �ֹ���

	int Defense; // ����
	int Shield; // ����

	float m_Speed = 500.f; // �ӵ�

	int Level;
	int Exp;
	int RewardExp; // óġ�� ����ġ

	int Camp; // ����
};

class CFieldObjScript :
	public CScript
{
protected:
	Vec2 NextIdx;
	Status m_status;

	CGameObject* m_Owner;
	CFieldScript* m_Field;
	bool IsPlayer;

	Vec2 CurFieldIdx;

	CDeck* m_Deck;



public:
	Status& GetStatus() { return m_status; }
	float GetMpPersent() { return m_status.Current_MP / m_status.MP; }
	void UseMana(int Mana);
	void SetStatus(const Status& _status) { m_status = _status; }
	void Shoot();
	void Cast();
	virtual void Hit(int Damage);
	void GetBuff();

	void FillMana();

	void AddMagic(CMagic* Magic);
	void SubMagic(string Name);


	void SetField(CFieldScript* _Field) { m_Field = _Field; }
	CFieldScript* GetField() { return m_Field; }

	void SetPlayer(bool input) { IsPlayer = input; }
	void SetOwner(CGameObject* _object) { m_Owner = _object; }

	Vec2 GetOwnerIdx() { return CurFieldIdx; }
	void SetOwnerIdx(Vec2 _index) { CurFieldIdx = _index; }

	Vec2 GetMoveIdx(Vec2 TargetDirIdx);

	virtual void begin() override;
	virtual void tick() override;

	virtual void SaveToFile(ofstream& _File) override;
	virtual void LoadFromFile(ifstream& _File) override;

public:
	CLONE(CFieldObjScript);
	CFieldObjScript();
	CFieldObjScript(const CFieldObjScript& _Origin);
	CFieldObjScript(UINT _SCRIPTYPE);
	~CFieldObjScript();
};
