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

	// 수정이 필요. 여러개를 어떻게 다룰 것인가? 하나의 포인터인데,
	/*CGameObject* temp = obj->Clone();
	iconlist.push_back(temp);
	GamePlayStatic::SpawnGameObject(temp, LayerDefault);*/

	this->SetName(L"MagicManager");
}

MagicManager::~MagicManager()
{
}
