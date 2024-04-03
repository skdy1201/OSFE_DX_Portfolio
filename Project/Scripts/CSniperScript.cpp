#include "pch.h"
#include "CSniperScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include "CFieldObjScript.h"

CSniperScript::CSniperScript()
	: CScript((UINT)STATE_TYPE::SNIPERIDLESTATE)
	, m_MoveCooltime(0.f)
	, 

{
}

CSniperScript::~CSniperScript()
{
}

void CSniperScript::begin()
{
	if (StateMachine())
	{
		CGameObject* pPlayer = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
		if (pPlayer)
		{
			StateMachine()->AddBlackboardData(L"TargetObject", BB_DATA::OBJECT, pPlayer);
		}

		if (nullptr != StateMachine()->GetFSM())
		{
			StateMachine()->GetFSM()->SetState(L"IdleState");
		}

	}

	

	StateMachine()->AddBlackboardData(L"MoveCooldown", BB_DATA::FLOAT, &m_MoveCooltime);
	StateMachine()->AddBlackboardData(L"Current Row", BB_DATA::INT, &CurRow);

}

void CSniperScript::tick()
{
	if(m_MoveCooltime <= 3.f)
	{
		m_MoveCooltime += DT;
	}

	CurRow = (int)OwnerFojScript->GetOwnerIdx().y;
}

void CSniperScript::SaveToFile(ofstream& _File)
{
}

void CSniperScript::LoadFromFile(ifstream& _File)
{
}
