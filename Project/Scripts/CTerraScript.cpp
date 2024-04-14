#include "pch.h"
#include "CTerraScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>


CTerraScript::CTerraScript()
	: CFieldObjScript((UINT)SCRIPT_TYPE::TERRASCRIPT)
	, m_MoveCooltime(0.f)
	,m_AttackCooltime(0.f)
	,m_HurtTime(0)
{
}

CTerraScript::~CTerraScript()
{
}

void CTerraScript::begin()
{
	m_status.HP = 10.f;
	m_status.Current_HP = m_status.HP;
	m_status.Camp = 2;

	m_Owner = this->GetOwner();

	if (StateMachine())
	{

		StateMachine()->AddBlackboardData(L"MoveCooldown", BB_DATA::FLOAT, &m_MoveCooltime);
		StateMachine()->AddBlackboardData(L"AttackCooldown", BB_DATA::FLOAT, &m_AttackCooltime);

		StateMachine()->AddBlackboardData(L"Owner", BB_DATA::OBJECT, this->GetOwner());

		CGameObject* pPlayer = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
		if (pPlayer)
		{
			StateMachine()->AddBlackboardData(L"Player", BB_DATA::OBJECT, pPlayer);
		}

		if (nullptr != StateMachine()->GetFSM())
		{
			StateMachine()->GetFSM()->ChangeState(L"CTerraEntryState");
		}

	}

}

void CTerraScript::tick()
{
	if (m_MoveCooltime <= 10.f)
	{
		m_MoveCooltime += DT;
	}
}

void CTerraScript::Hit(int Damage)
{
	CFieldObjScript::Hit(Damage);
}

void CTerraScript::SaveToFile(ofstream& _File)
{
	CFieldObjScript::SaveToFile(_File);
}

void CTerraScript::LoadFromFile(ifstream& _File)
{
	CFieldObjScript::LoadFromFile(_File);
}
