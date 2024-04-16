#include "pch.h"
#include "CLurkerScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include "CFieldObjScript.h"


CLurkerScript::CLurkerScript()
	: CFieldObjScript((UINT)SCRIPT_TYPE::LURKERSCRIPT)
	, m_AttackCooltime(0.f)
	, m_HurtTime(0.f)
	, bMovedbyAttack(false)
{
}
	

 CLurkerScript::~CLurkerScript()
{
}

void CLurkerScript::begin()
{
	m_status.HP = 100;
	m_status.Current_HP = m_status.HP;
	m_status.Camp = 2;

	if (StateMachine())
	{
		StateMachine()->AddBlackboardData(L"AttackCooldown", BB_DATA::FLOAT, &m_AttackCooltime);

		StateMachine()->AddBlackboardData(L"Owner", BB_DATA::OBJECT, this->GetOwner());

		CGameObject* pPlayer = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
		if (pPlayer)
		{
			StateMachine()->AddBlackboardData(L"Player", BB_DATA::OBJECT, pPlayer);
		}

		if (nullptr != StateMachine()->GetFSM())
		{

			StateMachine()->GetFSM()->ChangeState(L"CLurkerIdleState");
		}

	}

}

void CLurkerScript::tick()
{
	if (m_AttackCooltime <= 8.5f)
	{
		m_AttackCooltime += DT;
	}

	if (b_Moved == true)
		bMovedbyAttack = true;
	else
		bMovedbyAttack = false;
}

void CLurkerScript::Hit(int Damage)
{
	CFieldObjScript::Hit(Damage);

}

void CLurkerScript::SaveToFile(ofstream& _File)
{
}

void CLurkerScript::LoadFromFile(ifstream& _File)
{
}
