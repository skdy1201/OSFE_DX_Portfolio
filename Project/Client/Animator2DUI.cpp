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

	//detail ui 생성
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

	// 현재 에니메이션 띄우기
	string CurAnimname;

	if (pAnim != nullptr)
	{
		CurAnimname = ToString(pAnim->GetName().c_str());
	}

	ImGui::Text("Current Animation");
	ImGui::SameLine();
	ImGui::InputText("##AnimName", (char*)CurAnimname.c_str(), CurAnimname.length(), ImGuiInputTextFlags_ReadOnly);


	// 콤보박스 선택 만들기

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

	ImGui::Text("Animation List:"); // 추가적인 설명 텍스트
	ImGui::SameLine(); // 콤보 박스와 같은 줄에 배치하기 위해

	static int item_current = 0;
	ImGui::Combo("##SelectAnimation", &item_current, items.data(), static_cast<int>(items.size()));


	// 콤보박스에 선택된 것을 재생하는 버튼,  바꾸는 것에 완벽한 결정이 나지 않았다.
	//일단 재생하는것만 바꾸는걸로 설정하기 + 굳이 다시 원본으로 바꿀 필요는 없는 것 같기도
	// 반복 여부만 하나 두자

	CAnim* pPrevAnim = pAnim; //임시로 하나 받아두기

	if (ImGui::Button("Change_Animation", ImVec2(150, 20)))
	{

		if (item_current >= 0 && item_current < Animlist.size())
		{
			pAnimator->Play(ToWString(Animlist[item_current]), CheckRepeat);

		}
	}

	ImGui::SameLine();

	//반복 체크박스
	ImGui::Text("Repeat"); ImGui::SameLine();
	ImGui::Checkbox("##AnimRepeat", &CheckRepeat);


	float maxwindowwidth = ImGui::GetContentRegionAvail().x;
	if (ImGui::Button("Detail AnimatorTool", ImVec2(maxwindowwidth, 20)))
	{
		m_ChildDetailUI->Activate();


	}


}