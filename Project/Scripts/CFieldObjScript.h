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

	int SpellPower; // 주문력

	int Defense; // 방어력
	int Shield; // 쉴드

	float m_Speed = 500.f; // 속도

	int Level;
	int Exp;
	int RewardExp; // 처치시 경험치

	int Camp; // 진영
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

	bool            b_Heat;

	bool			b_Moved;
	Vec2			MovedIdxDir;

public:
	Status& GetStatus() { return m_status; }
	float GetMpPersent() { return m_status.Current_MP / m_status.MP; }
	void UseMana(int Mana);
	void SetStatus(const Status& _status) { m_status = _status; }
	void Shoot();
	void Cast();
	virtual void Hit(int Damage);
	void GetBuff();

	bool GetHit() { return b_Heat; }
	void SetHit(bool _hit) { b_Heat = _hit; }

	void FillMana();

	void SetField(CFieldScript* _Field) { m_Field = _Field; }
	CFieldScript* GetField() { return m_Field; }

	void SetPlayer(bool input) { IsPlayer = input; }
	void SetOwner(CGameObject* _object) { m_Owner = _object; }

	Vec2 GetOwnerIdx() { return CurFieldIdx; }
	void SetOwnerIdx(Vec2 _index) { CurFieldIdx = _index; }

	Vec2 GetMoveIdx(Vec2 TargetDirIdx);

	CDeck* GetDeck() { return m_Deck; }

	void MovedByAttack();
	void SetbMoved(bool fact) { b_Moved = fact; }
	void SetMovedIdx(Vec2 idx) { MovedIdxDir = idx; }
	Vec2 GetMovedIdx() { return MovedIdxDir; }

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
