#include "pch.h"
#include "Animator2DUI.h"

#include <Engine\CAnimator2D.h>
#include <Engine\CAnim.h>

#include <Engine/CAssetMgr.h>
#include <Engine/CMeshRender.h>

#include "CImGuiMgr.h"
#include "ListUI.h"
#include "Inspector.h"

#include "CSubAnimator2DUI.h"

Animator2DUI::Animator2DUI()
	: ComponentUI("Animator2D", "##Animator2D", COMPONENT_TYPE::ANIMATOR2D)
{
	SetSize(ImVec2(0.f, 120.f));
	SetComponentTitle("Animator2D");

	//detail ui ����
	m_ChildDetailUI = new CSubAnimator2DUI(this);
	AddChildUI(m_ChildDetailUI);
	m_ChildDetailUI->Deactivate();
}

Animator2DUI::~Animator2DUI()
{
}


void Animator2DUI::render_update()
{
	pTarget = GetTargetObject();

	if (nullptr == GetTargetObject())
		return;

	ComponentUI::render_update();

	CAnimator2D* pAnimator = pTarget->Animator2D();
	CAnim* pAnim = pAnimator->GetCurAnim();

	// ���� ���ϸ��̼� ����
	string CurAnimname;

	if (pAnim != nullptr)
	{
		CurAnimname = ToString(pAnim->GetName().c_str());
	}

	ImGui::Text("Current Animation");
	ImGui::SameLine();
	ImGui::InputText("##AnimName", (char*)CurAnimname.c_str(), CurAnimname.length(), ImGuiInputTextFlags_ReadOnly);


	// �޺��ڽ� ���� �����

	map<wstring, CAnim*> temp = *pAnimator->GetAnimmap();
	vector<string> Animlist;


	for (const auto pair : temp)
	{
		Animlist.push_back(ToString(pair.first));
	}

	vector<const char*> items;

	for (const auto& name : Animlist)
	{
		items.push_back(name.c_str());
	}

	ImGui::Text("Animation List:"); // �߰����� ���� �ؽ�Ʈ
	ImGui::SameLine(); // �޺� �ڽ��� ���� �ٿ� ��ġ�ϱ� ����

	static int item_current = 0;
	ImGui::Combo("##SelectAnimation", &item_current, items.data(), static_cast<int>(items.size()));


	// �޺��ڽ��� ���õ� ���� ����ϴ� ��ư,  �ٲٴ� �Ϳ� �Ϻ��� ������ ���� �ʾҴ�.
	//�ϴ� ����ϴ°͸� �ٲٴ°ɷ� �����ϱ� + ���� �ٽ� �������� �ٲ� �ʿ�� ���� �� ���⵵
	// �ݺ� ���θ� �ϳ� ����

	CAnim* pPrevAnim = pAnim; //�ӽ÷� �ϳ� �޾Ƶα�

	if (ImGui::Button("Change_Animation", ImVec2(150, 20)))
	{

		if (item_current >= 0 && item_current < Animlist.size())
		{
			pAnimator->Play(ToWString(Animlist[item_current]), CheckRepeat);

		}
	}

	ImGui::SameLine();

	//�ݺ� üũ�ڽ�
	ImGui::Text("Repeat"); ImGui::SameLine();
	ImGui::Checkbox("##AnimRepeat", &CheckRepeat);


	float maxwindowwidth = ImGui::GetContentRegionAvail().x;
	if (ImGui::Button("Detail AnimatorTool", ImVec2(maxwindowwidth, 20)))
	{
		m_ChildDetailUI->Activate();


	}


}