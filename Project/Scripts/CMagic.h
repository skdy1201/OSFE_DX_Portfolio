#pragma once
enum class KeyWard
{
	Trinity,
	Anima,
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

	bool			CastRange[MagicFieldIndexY][MagicFieldIndexX]; // 마법 계산시 발동하는 idx 들을 담는 벡터. 시작 위치는 따로

	//buff 구조체 추가 예정. 시스템이 구현된다면
	// 설명카드 추가 가능성 string 부분
};
class CMagic
{
protected:

	CGameObject*			Caster;
	Magic_Info				m_Info;
	Vec2					CenterPoint; // 주문 범위 계산 좌표의 원점
	Vec2					StartPoint; // 실제 타일에서의 발동 위치

	class CFieldScript* CurField;
public:
	void SetCaster(CGameObject* __Caster);
	virtual void cast(Vec2 StartPoint) = 0;

	void SetField(CFieldScript* Field) { CurField = Field; }
	CFieldScript* GetField() { return CurField; }

	Magic_Info GetMagicInfo() { return m_Info; }

public:
	CMagic();
	virtual ~CMagic();
};
