#include "pch.h"
#include "StateMachineUI.h"

#include <Engine/CStateMachine.h>


StateMachineUI::StateMachineUI()
	:ComponentUI("StateMachine", "##SM", COMPONENT_TYPE::STATEMACHINE)
{
	SetSize(ImVec2(0.f, 120.f));
	SetComponentTitle("StateMachine");
}

StateMachineUI::~StateMachineUI()
{
}


void StateMachineUI::render_update()
{
	ComponentUI::render_update();

	SelectFSM();

	if (m_FSM.Get())
		CurrentState();

	if (m_FSM.Get())
		StateList();

}

void StateMachineUI::Activate()
{
	ComponentUI::Activate();

	m_stateMachine = (CStateMachine*)GetTargetObject()->GetComponent(COMPONENT_TYPE::STATEMACHINE);
}


#include "ListUI.h"
void StateMachineUI::SelectFSM()
{
	string fsmname;
	m_FSM = m_stateMachine->GetOriginFSM();

	if(m_FSM != nullptr)
	{
		fsmname = ToString(m_FSM->GetRelativePath()).c_str();
	}

	ImGui::Text("FSM ");
	ImGui::SameLine();
	ImGui::InputText("##FSMName", (char*)fsmname.c_str(), fsmname.length(), ImGuiInputTextFlags_ReadOnly);

	// Mesh Drop üũ
	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");

		if (payload)
		{
			DWORD_PTR data = *((DWORD_PTR*)payload->Data);
			CAsset* pAsset = (CAsset*)data;
			if (ASSET_TYPE::FSM == pAsset->GetType())
			{
				m_stateMachine->SetFSM((CFSM*)pAsset);
			}
		}

		ImGui::EndDragDropTarget();
	}

	ImGui::SameLine();
	if (ImGui::Button("##FSMBtn", ImVec2(20, 20)))
	{
		// ����Ʈ UI
		ListUI* pListUI = (ListUI*)CImGuiMgr::GetInst()->FindUI("##List");

		vector<string> vecFSMName;
		CAssetMgr::GetInst()->GetAssetName(ASSET_TYPE::FSM, vecFSMName);

		pListUI->AddString(vecFSMName);
		//pListUI->SetDbClickCallBack(MeshSelect);
		pListUI->SetDbClickDelegate(this, (Delegate_1)&StateMachineUI::FSMSelect);
		pListUI->Activate();
	}
}

void StateMachineUI::CurrentState()
{
	CState* state = m_stateMachine->GetFSM()->GetCurState();

	ImGui::Text("CurState");
	ImGui::SameLine();
	string name;

	if (state != nullptr)
		name = ToString(state->GetName());
	ImGui::InputText("##cursatteName", (char*)name.c_str(), name.length(), ImGuiInputTextFlags_ReadOnly);
}

void StateMachineUI::StateList()
{
	map<wstring, CState*>& states = m_FSM->GetStates();

	for(auto iter = states.begin(); iter != states.end(); ++iter)
	{
		string statename = ToString(iter->first);
		ImGui::InputText("##statename", (char*)statename.c_str(), statename.length(), ImGuiInputTextFlags_ReadOnly);
		ImGui::SameLine();

		if (ImGui::Button("Change"))
		{
			m_stateMachine->SetFSM(m_FSM);
			m_stateMachine->GetFSM()->ChangeState(iter->first);
		}

		SetSize(ImVec2(0, 80 + states.size() * 25));

	}
}


void StateMachineUI::FSMSelect(DWORD_PTR _ptr)
{
	string strMesh = (char*)_ptr;
	wstring strMeshName = ToWString(strMesh);

	Ptr<CFSM> pFSM = CAssetMgr::GetInst()->FindAsset<CFSM>(strMeshName);

	m_stateMachine->SetFSM(pFSM);
}
