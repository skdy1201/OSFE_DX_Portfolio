#include "pch.h"
#include "PrefabUI.h"

#include <Engine/CGameObject.h>

#include "Engine/CPrefab.h"

PrefabUI::PrefabUI()
	: AssetUI("Prefab", "##Prefab", ASSET_TYPE::PREFAB)
{
}

PrefabUI::~PrefabUI()
{
}

void PrefabUI::render_update()
{
    Ptr<CPrefab> pPrefab = (CPrefab*)GetAsset().Get();
    string strPath = ToString(pPrefab->GetRelativePath());

    ImGui::Text("Prefab");
    ImGui::SameLine();
    ImGui::InputText("##PrefabName", (char*)strPath.c_str(), strPath.length(), ImGuiInputTextFlags_ReadOnly);


    if (ImGui::Button("Spawn"))
    {
        CGameObject* pNewObj = pPrefab->Instantiate();
        Vec3 vPos = pNewObj->Transform()->GetRelativePos();
        pNewObj->Transform()->SetRelativePos(vPos);

        int LayerNum = pPrefab->GetPrefabIndex();

        GamePlayStatic::SpawnGameObject(pNewObj, LayerNum);
    }
}