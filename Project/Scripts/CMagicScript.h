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

	int				Dmg; // �ٴ��̸� �ݴ�� ������ �������
	int				TotalHit;

	CGameObject*	Caster;
	vector<Vec2>	CastRange; // �ߵ��ϴ� idx ���� ��� ����

	//buff ����ü �߰� ����. �ý����� �����ȴٸ�
	// ����ī�� �߰� ���ɼ� string �κ�
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

