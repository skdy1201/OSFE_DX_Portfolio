#pragma once

#include <Engine/CScript.h>

class CFieldObjScript;
class Terraform;

class CTerraAttackState :
    public CState
{
	CGameObject* Terra;
	CFieldObjScript* TerraScript;
	Ptr<CPrefab> AnimatorObject;


	Terraform* m_Terraform;

	int AttackPattern;
	bool bAttack;

	CGameObject* CheckAnimation[4];

	float* AttackTimer;
	float* MoveTimer;

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

