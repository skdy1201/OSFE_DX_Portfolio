#include "pch.h"
#include "Inspector.h"

#include <Engine/CTransform.h>
#include <Engine/CLevelMgr.h>

#include "TransformUI.h"
#include "MeshRenderUI.h"
#include "Collider2DUI.h"
#include "Light2DUI.h"
#include "Animator2DUI.h"
#include "ScriptUI.h"

#include "AssetUI.h"



Inspector::Inspector()
	: UI("Inspector", "##Inspector")
	, m_TargetObject(nullptr)
	, m_arrComUI{}
{
	// �ڽ� UI ����
	CreateChildUI();
}

Inspector::~Inspector()
{

}

void Inspector::tick()
{
}

void Inspector::render_update()
{
	if (nullptr == m_TargetObject)
		return;

	if (nullptr != m_TargetObject)
	{
		string strName = string(m_TargetObject->GetName().begin(), m_TargetObject->GetName().end());
		ImGui::Text(strName.c_str());

		ImGui::NewLine();

		string TargetLayer = to_string(m_TargetObject->GetLayerIdx());
		ImGui::Text("Object Layer Index : %s", TargetLayer.c_str());


		string change_idx = "Change Object Index : ";
		ImGui::Text(change_idx.c_str());

		ImGui::SameLine();

		static char idxtemp[99] = " ";
		static string inputnum = "";

		ImGui::SetNextItemWidth(30.0f); // ���� ������ �ʺ� 100 �ȼ��� ����
		if(ImGui::InputText("##Change Layer", idxtemp, IM_ARRAYSIZE(idxtemp)))
		{
			inputnum = idxtemp;
		}

		ImGui::SameLine();

		if(ImGui::Button("##change Obj Index", ImVec2{ 10.f, 10.f }))
		{
			int changeidx = stoi(inputnum);
			CLevelMgr::GetInst()->ChangeObjectIdx(m_TargetObject, changeidx);

			
		}
	}
}


void Inspector::SetTargetObject(CGameObject* _Object)
{
	// Target ������Ʈ ����
	m_TargetObject = _Object;

	// �ش� ������Ʈ�� �����ϰ� �ִ� ������Ʈ�� �����ϴ� ������ƮUI Ȱ��ȭ
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrComUI[i])
		{
			m_arrComUI[i]->SetTargetObject(_Object);
		}
	}

	// �ش� ������Ʈ�� �����ϰ� �ִ� Script �� ���߾ ScriptUI �� Ȱ��ȭ ��Ų��.
	if (nullptr == _Object)
	{
		for (size_t i = 0; i < m_vecScriptUI.size(); ++i)
		{
			m_vecScriptUI[i]->Deactivate();
		}
	}
	else
	{
		for (size_t i = 0; i < m_vecScriptUI.size(); ++i)
		{
			m_vecScriptUI[i]->Deactivate();
		}
		
		ResizeScriptUI(_Object->GetScripts().size());

		const vector<CScript*>& vecScripts = _Object->GetScripts();
		for (size_t i = 0; i < vecScripts.size(); ++i)
		{
			m_vecScriptUI[i]->SetScript(vecScripts[i]);			
		}
	}


	// AssetUI ��Ȱ��ȭ
	for (UINT i = 0; i < (UINT)ASSET_TYPE::END; ++i)
	{
		m_arrAssetUI[i]->Deactivate();
	}
}

void Inspector::SetTargetAsset(Ptr<CAsset> _Asset)
{
	SetTargetObject(nullptr);

	m_TargetAsset = _Asset;

	for (UINT i = 0; i < (UINT)ASSET_TYPE::END; ++i)
	{
		m_arrAssetUI[i]->Deactivate();
	}
		
	if(nullptr != m_TargetAsset)
	{
		m_arrAssetUI[(UINT)m_TargetAsset->GetType()]->Activate();
		m_arrAssetUI[(UINT)m_TargetAsset->GetType()]->SetAsset(_Asset);
	}	
}
