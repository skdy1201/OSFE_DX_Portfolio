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

	int				Dmg; // �ٴ��̸� �ݴ�� ������ �������
	int				TotalHit;

	bool			CastRange[MagicFieldIndexY][MagicFieldIndexX]; // ���� ���� �ߵ��ϴ� idx ���� ��� ����. ���� ��ġ�� ����

	//buff ����ü �߰� ����. �ý����� �����ȴٸ�
	// ����ī�� �߰� ���ɼ� string �κ�
};
class CMagic
{
protected:

	CGameObject*			Caster;
	Magic_Info				m_Info;
	Vec2					CenterPoint; // �ֹ� ���� ��� ��ǥ�� ����
	Vec2					StartPoint; // ���� Ÿ�Ͽ����� �ߵ� ��ġ

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
