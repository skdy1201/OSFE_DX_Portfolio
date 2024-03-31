#include "pch.h"
#include "CFieldObjScript.h"
#include "CFieldScript.h"

#include "CProjectileScript.h"


CFieldObjScript::CFieldObjScript()
	: CScript((UINT)SCRIPT_TYPE::FIELDOBJSCRIPT)
	, m_Health{}
	, IsPlayer(true)

{

}

CFieldObjScript::CFieldObjScript(const CFieldObjScript& _Origin)
	: CScript((UINT)SCRIPT_TYPE::FIELDOBJSCRIPT)
{
}

CFieldObjScript::~CFieldObjScript()
{
}

void CFieldObjScript::Move()
{
	if(IsPlayer == true)
	{
		if(KEY_TAP(KEY::UP))
		{
			Vec2 Index = GetOwnerIdx();

			Vec2 NextIndex = { Index.x, Index.y + 1 };

			if (NextIndex.y >= TileMaxRow)
				return;

			m_Field->MoveToTile(m_Owner, NextIndex);
			SetOwnerIdx(NextIndex);


		}

		if (KEY_TAP(KEY::DOWN))
		{
			Vec2 Index = GetOwnerIdx();

			Vec2 NextIndex = { Index.x, Index.y - 1 };

			if (NextIndex.y < 0)
				return;
				
			m_Field->MoveToTile(m_Owner, NextIndex);
			SetOwnerIdx(NextIndex);
		}

			if (KEY_TAP(KEY::LEFT))
			{
				Vec2 Index = GetOwnerIdx();

				Vec2 NextIndex = { Index.x - 1, Index.y };

				m_Field->MoveToTile(m_Owner, NextIndex);
				SetOwnerIdx(NextIndex);
			}

			if (KEY_TAP(KEY::RIGHT))
			{
				Vec2 Index = GetOwnerIdx();

				Vec2 NextIndex = { Index.x + 1, Index.y};

				m_Field->MoveToTile(m_Owner, NextIndex);
				SetOwnerIdx(NextIndex);
			}

	}
}

void CFieldObjScript::Shoot()
{
	if (KEY_TAP(KEY::E))
	{
		CGameObject* GameObj;
		Ptr<CPrefab> prefab = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\PlayerBullet.pref", L"prefab\\PlayerBullet.pref");
		GameObj = prefab->Instantiate();


		CProjectileScript* pProjScript = GameObj->GetScript<CProjectileScript>();
		pProjScript->SetShooter(m_Owner);

		CFieldScript* pFieldScript = this->GetField();

		Vec3 ProjTransform = m_Owner->Transform()->GetWorldPos();
		ProjTransform.x += 10.f;
		ProjTransform.z = ProjZ;
		GameObj->Transform()->SetRelativePos(ProjTransform);

		pProjScript->SetIndex(this->CurFieldIdx);
		pProjScript->SetField(pFieldScript);

		GamePlayStatic::SpawnGameObject(GameObj, 0);

	}
}



void CFieldObjScript::begin()
{
}

void CFieldObjScript::tick()
{
	Move();
	Shoot();
}

void CFieldObjScript::SaveToFile(ofstream& _File)
{
}

void CFieldObjScript::LoadFromFile(ifstream& _File)
{
}
