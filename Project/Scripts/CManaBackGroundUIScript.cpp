#include "pch.h"
#include "CManaBackGroundUIScript.h"

CManaBackGroundUIScript::CManaBackGroundUIScript()
	: CUIScript((UINT)SCRIPT_TYPE::MANABACKGROUNDUISCRIPT)
	, PlayerMana(4.f)
	, CurMana(0.f)

{
}

CManaBackGroundUIScript::~CManaBackGroundUIScript()
{
}

void CManaBackGroundUIScript::begin()
{
	CUIScript::begin();

	for(int i = 1; i < PlayerMana; ++i)
	{
		Vec3 ManaBarPos = pObj->Transform()->GetWorldPos();
		ManaBarPos.z = 0.f;

		Vec3 ManaBarScale = pObj->Transform()->GetRelativeScale();

		CGameObject* pOBJ;
		pOBJ = CPrefab::GetPrefabObj(PrefabManaLine);

		ManaBarPos.x = (ManaBarPos.x - (ManaBarScale.x/2)) + ((ManaBarScale.x / PlayerMana) * i);

		pOBJ->Transform()->SetRelativePos(ManaBarPos);
		GamePlayStatic::SpawnGameObject(pOBJ, 31);

	}
}

void CManaBackGroundUIScript::tick()
{
}

void CManaBackGroundUIScript::SaveToFile(ofstream& _File)
{
	CUIScript::SaveToFile(_File);
}

void CManaBackGroundUIScript::LoadFromFile(ifstream& _File)
{
	CUIScript::LoadFromFile(_File);
}
