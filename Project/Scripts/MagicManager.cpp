#include "pch.h"
#include "MagicManager.h"

#include <Engine/CTransform.h>

MagicManager::MagicManager()
{
	CGameObject* obj;
	obj = CPrefab::GetPrefabObj(PrefabFrosticon);

	obj->Transform()->SetRelativePos(Vec3{ 0.f, 0.f, MagicHideZ });
	iconlist.push_back(obj);
	GamePlayStatic::SpawnGameObject(obj, LayerDefault);

	// ������ �ʿ�. �������� ��� �ٷ� ���ΰ�? �ϳ��� �������ε�,
	/*CGameObject* temp = obj->Clone();
	iconlist.push_back(temp);
	GamePlayStatic::SpawnGameObject(temp, LayerDefault);*/

	this->SetName(L"MagicManager");
}

MagicManager::~MagicManager()
{
}
