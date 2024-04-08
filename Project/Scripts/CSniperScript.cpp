#include "pch.h"
#include "CSniperScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include "CFieldObjScript.h"


CSniperScript::CSniperScript()
	: CFieldObjScript((UINT)SCRIPT_TYPE::SNIPERSCRIPT)
	, m_MoveCooltime(0.f)
	, MoveDir(0)
    , m_AttackCooltime(0)
	, m_HurtTime(0)
{
}

CSniperScript::~CSniperScript()
{
}

void CSniperScript::begin()
{
	m_status.HP = 500000000;
	m_status.Current_HP = m_status.HP;
	m_status.Camp = 2;

	if (StateMachine())
	{

		StateMachine()->AddBlackboardData(L"MoveCooldown", BB_DATA::FLOAT, &m_MoveCooltime);
		StateMachine()->AddBlackboardData(L"AttackCooldown", BB_DATA::FLOAT, &m_AttackCooltime);
		StateMachine()->AddBlackboardData(L"Current Row", BB_DATA::INT, &CurRow);
		StateMachine()->AddBlackboardData((L"Move Dir"), BB_DATA::INT, &MoveDir);

		StateMachine()->AddBlackboardData(L"Owner", BB_DATA::OBJECT, this->GetOwner());

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

	//자식애니메이터 소환하기

	CGameObject* Obj;
	Obj = CPrefab::GetPrefabObj(L"prefab\\SniperCharge.pref");
	Obj->Transform()->SetRelativePos(Vec3{ 34.f ,63.f, 1.f });

	Ptr<CMaterial> pMtrl = Obj->MeshRender()->GetMaterial();
	pMtrl->SetScalarParam(SCALAR_PARAM::INT_0, 0);

	ChildAnim = Obj;
	GamePlayStatic::SpawnGameObject(Obj, 0);

	this->GetOwner()->AddChild(Obj);

	StateMachine()->AddBlackboardData(L"ChildAnim", BB_DATA::OBJECT, Obj);


	//ChildAnim->Animator2D()->Play(L"EmptyAnimation", true);
}

void CSniperScript::tick()
{
	if(m_MoveCooltime <= 3.f)
	{
		m_MoveCooltime += DT;
	}

	if(m_AttackCooltime  <= 5.f)
	{
		m_AttackCooltime += DT;
	}

	CurRow = (int)OwnerFojScript->GetOwnerIdx().y;

	if(m_HurtTime > 0.f && m_status.Current_HP > 0)
	{
		m_Owner->GetRenderComopnent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, 0);
		m_HurtTime -= DT;
	}
	else if(m_HurtTime <= 0.f)
	{
		m_Owner->GetRenderComopnent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, 1);
		m_HurtTime = 0.f;

	}


}

void CSniperScript::Hit(int Damage)
{
	CFieldObjScript::Hit(Damage);

	m_HurtTime += 0.2f;
}

void CSniperScript::SaveToFile(ofstream& _File)
{
}

void CSniperScript::LoadFromFile(ifstream& _File)
{
}
