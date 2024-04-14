#pragma once

#include <Engine/CScript.h>

class DiagBeamMagic;
class CDiagBeam;
class CFieldObjScript;
class Terraform;
class BossDiscMagic;

class CTerraAttackState :
    public CState
{
	CGameObject* Terra;
	CFieldObjScript* TerraScript;
	Ptr<CPrefab> AnimatorObject;


	Terraform* m_Terraform;
	DiagBeamMagic* m_DiagBeam;
	BossDiscMagic* m_Disc;

	int AttackPattern;
	bool bAttack;


	Vec2 DiscIdx[2];
	CGameObject* CheckAnimation[4];

	float* AttackTimer;
	float* MoveTimer;

	bool IsExit;

public:
	void Attack1();
	void Attack2();
	void Attack3();

	bool CheckEndAnim();

public:

	virtual void finaltick() override;
	virtual void Enter() override;
	virtual void Exit() override;

public:
	CTerraAttackState();
	~CTerraAttackState();
};

