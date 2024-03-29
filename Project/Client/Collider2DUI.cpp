#include "pch.h"
#include "Collider2DUI.h"

#include <Engine\CCollider2D.h>
#include <Engine\\CRenderMgr.h>

#include "Inspector.h"


Collider2DUI::Collider2DUI()
	: ComponentUI("Collider2D", "##Collider2D", COMPONENT_TYPE::COLLIDER2D)
{
	SetSize(ImVec2(0.f, 120.f));
	SetComponentTitle("Collider2D");
}

Collider2DUI::~Collider2DUI()
{
}

void Collider2DUI::render_update()
{
	if (nullptr == GetTargetObject())
		return;

	ComponentUI::render_update();

	Vec2 ColPos = GetTargetObject()->Collider2D()->GetOffsetPos();
	float ParamPos[2] = { ColPos.x, ColPos.y };

	Vec2 ColScale = GetTargetObject()->Collider2D()->GetOffsetScale();
	float ParamScale[2] = { ColScale.x, ColScale.y };

	COLLIDER2D_TYPE COL_Type;
	COL_Type = GetTargetObject()->Collider2D()->GetType();

	ImGui::Text("ColPosition"); ImGui::SameLine(); ImGui::DragFloat2("##Relative Position", ParamPos);
	ImGui::Text("ColScale   "); ImGui::SameLine(); ImGui::DragFloat2("##Relative Scale", ParamScale);
	ImGui::Text("Type      "); ImGui::SameLine(); ImGui::SmallButton("Change Collider Type");
	if (ImGui::IsItemClicked())
	{
		if (COL_Type == COLLIDER2D_TYPE::RECT)
		{
			GetTargetObject()->Collider2D()->SetColliderType(COLLIDER2D_TYPE::CIRCLE);
		}
		else if (COL_Type == COLLIDER2D_TYPE::CIRCLE)
		{
			GetTargetObject()->Collider2D()->SetColliderType(COLLIDER2D_TYPE::RECT);
		}

	}



	ColPos.x = ParamPos[0]; ColPos.y = ParamPos[1];
	ColScale.x = ParamScale[0]; ColScale.y = ParamScale[1];

	GetTargetObject()->Collider2D()->SetOffsetPos(ColPos);
	GetTargetObject()->Collider2D()->SetOffsetScale(ColScale);



	// Absolute °ª 
	bool bAbsolute = GetTargetObject()->Collider2D()->IsAbsolute();

	if (ImGui::Checkbox("Is Absolute", &bAbsolute))
	{
		GetTargetObject()->Collider2D()->SetAbsolute(bAbsolute);
	}

	// Absolute °ª 
	bool bDrawDebug = CRenderMgr::GetInst()->IsDebugPosition();

	if (ImGui::Checkbox("Debug Draw", &bDrawDebug))
	{
		CRenderMgr::GetInst()->SetDebugPosition(bDrawDebug);
	}



}

