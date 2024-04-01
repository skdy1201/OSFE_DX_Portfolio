#pragma once

#include <Engine/CScript.h>

enum class KeyWard
{
	Trinity,
	end
};

enum class MagicType
{
	Shot,
	Ground,
	Summon,
	end
};

struct Magic_Info
{
	int				ManaCost;

	string			SpellName;
	KeyWard			m_keyWard;
	MagicType		m_Type;

	int				Dmg; // 다단이면 반대로 나눠서 계산하자
	int				TotalHit;

	CGameObject*	Caster;
	vector<Vec2>	CastRange; // 발동하는 idx 들을 담는 벡터. 시작 위치를 무조건 첫번째에 넣자

	//buff 구조체 추가 예정. 시스템이 구현된다면
	// 설명카드 추가 가능성 string 부분
};

class CMagicScript :
    public CScript
{
private:

	class CFieldScript*		CurField;
	Vec2					StartIdx;

	Magic_Info				m_MagicInfo;
	vector<vector<bool>>	MagicField;


public:

	void Set_MagicInfo(Magic_Info _NewInfo) { m_MagicInfo = _NewInfo; }
	Magic_Info Get_MagicInfo() { return m_MagicInfo; }

	void SetMagicField();
	vector<vector<bool>>& CalculateRange(Vec2 _StartIdx);
	virtual void Cast() {};

	virtual void begin() override;
	virtual void tick() override;

	virtual void SaveToFile(ofstream& _File) override;
	virtual void LoadFromFile(ifstream& _File) override;

public:
	CLONE(CMagicScript);
	CMagicScript();
	CMagicScript(const CMagicScript& _Origin);
	~CMagicScript();
};

