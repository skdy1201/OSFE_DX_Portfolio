#include "pch.h"
#include "CControlScript.h"

#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>

#include <Engine/CAssetMgr.h>



CControlScript::CControlScript()
	: CScript((UINT)SCRIPT_TYPE::CONTROLSCRIPT)
{
}

CControlScript::~CControlScript()
{
}

void CControlScript::begin()
{
}

void CControlScript::tick()
{
	if(KEY_TAP(KEY::M))
	{
		GamePlayStatic::Play2DBGM(L"sound\\Battle_of_Ice_I.wav", 0.5f);
		GamePlayStatic::Play2DSound( L"sound\\shuffle_start.wav", 1, 0.5f);

		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CGameObject* pObj = nullptr;

		Ptr<CPrefab> temp = CAssetMgr::GetInst()->Load<CPrefab>(FieldPrefabKey, FieldPrefabKey);
		pObj = temp->Instantiate();
		GamePlayStatic::SpawnGameObject(pObj, LayerField);

		temp = CAssetMgr::GetInst()->Load<CPrefab>(PrefabManaUI, PrefabManaUI);
		pObj = temp->Instantiate();
		GamePlayStatic::SpawnGameObject(pObj, LayerUI);


		temp = CAssetMgr::GetInst()->Load<CPrefab>(PrefabDeckCoverUI, PrefabDeckCoverUI);
		pObj = temp->Instantiate();
		GamePlayStatic::SpawnGameObject(pObj, LayerUI);


		temp = CAssetMgr::GetInst()->Load<CPrefab>(PrefabHandSlotQ, PrefabHandSlotQ);
		pObj = temp->Instantiate();
		GamePlayStatic::SpawnGameObject(pObj, LayerUI);


		temp = CAssetMgr::GetInst()->Load<CPrefab>(PrefabHandSlotW, PrefabHandSlotW);
		pObj = temp->Instantiate();
		GamePlayStatic::SpawnGameObject(pObj, LayerUI);


		temp = CAssetMgr::GetInst()->Load<CPrefab>(PrefabTopInfo, PrefabTopInfo);
		pObj = temp->Instantiate();
		GamePlayStatic::SpawnGameObject(pObj, LayerUI);

	}

	if(KEY_TAP((KEY::B)))
	{
		GamePlayStatic::Play2DBGM(L"sound\\Mystery.wav", 0.5f);

		CGameObject* obj = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"UICamera");
		obj->Camera()->LayerCheck(31, false);


		Ptr<CPrefab> temp = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\ExitLobby.pref", L"prefab\\ExitLobby.pref");
		CGameObject* pObj = temp->Instantiate();

		Vec3 Pos = pObj->Transform()->GetRelativePos();
		

		pObj->Transform()->SetRelativePos(Pos);

		GamePlayStatic::SpawnGameObject(pObj, LayerBackGround);
	}
}

void CControlScript::SaveToFile(ofstream& _File)
{
}

void CControlScript::LoadFromFile(ifstream& _File)
{
}
