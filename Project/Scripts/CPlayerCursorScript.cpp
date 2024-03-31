#include "pch.h"
#include "CPlayerCursorScript.h"

#include "CFieldScript.h"
#include "CFieldObjScript.h"

#include <Engine/CGameObject.h>
#include <Engine/CComponent.h>


CPlayerCursorScript::CPlayerCursorScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERCURSORSCRIPT)
	, m_PlayerScript(nullptr)
	, m_Field(nullptr)
	, AttackRange(0.f, 0.f)
	, CurIndex(0.f, 0.f)
{
}

CPlayerCursorScript::CPlayerCursorScript(const CPlayerCursorScript& _Origin)
	: CScript((UINT)SCRIPT_TYPE::PLAYERCURSORSCRIPT)
	, m_PlayerScript(nullptr)
	, m_Field(nullptr)
	, AttackRange(0.f, 0.f)
	, CurIndex(0.f, 0.f)
{
}

CPlayerCursorScript::~CPlayerCursorScript()
{
}

void CPlayerCursorScript::begin()
{
	Vec2 CursorPos = PlayerAttackRange* Vec2{ TileX + Tilespacex, TileY + Tilespacey };
	Transform()->SetRelativePos(Vec3(CursorPos.x, CursorPos.y, CursorZ));
}

void CPlayerCursorScript::tick()
{

}

void CPlayerCursorScript::SaveToFile(ofstream& _File)
{
}

void CPlayerCursorScript::LoadFromFile(ifstream& _File)
{
}
