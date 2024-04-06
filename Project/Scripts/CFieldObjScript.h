#pragma once

#include <Engine/CScript.h>

class CMagic;

class CFieldScript;

struct Status
{
	CGameObject* Owner;
	int HP;
	int MP;

	int Current_HP;
	int Current_MP;

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
private:
	Vec2 NextIdx;
	Status m_status;

	CGameObject* m_Owner;
	CFieldScript* m_Field;
	bool IsPlayer;

	Vec2 CurFieldIdx;

	int temp;

public:
	Status& GetStatus() { return m_status; }
	void SetStatus(const Status& _status) { m_status = _status; }
	void Shoot();
	void Cast();

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
