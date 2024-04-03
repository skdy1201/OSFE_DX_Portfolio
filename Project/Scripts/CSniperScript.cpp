#include "pch.h"
#include "CSniperScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include "CFieldObjScript.h"

CSniperScript::CSniperScript()
	: CScript((UINT)SCRIPT_TYPE::SNIPERSCRIPT)
	, m_MoveCooltime(0.f)
	, MoveDir(0)
{
}

CSniperScript::~CSniperScript()
{
}

void CSniperScript::begin()
{
	if (StateMachine())
	{

		StateMachine()->AddBlackboardData(L"MoveCooldown", BB_DATA::FLOAT, &m_MoveCooltime);
		StateMachine()->AddBlackboardData(L"Current Row", BB_DATA::INT, &CurRow);

		StateMachine()->AddBlackboardData(L"Owner", BB_DATA::OBJECT, this->GetOwner());

		StateMachine()->AddBlackboardData((L"Move Dir"), BB_DATA::INT, &MoveDir);

		CGameObject* pPlayer = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
		if (pPlayer)
		{
			StateMachine()->AddBlackboardData(L"Player", BB_DATA::OBJECT, pPlayer);
		}

		if (nullptr != StateMachine()->GetFSM())
		{
			StateMachine()->GetFSM()->ChangeState(L"CSniperIdleState");
		}

	}

	
	OwnerFojScript = GetOwner()->GetScript<CFieldObjScript>();

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
