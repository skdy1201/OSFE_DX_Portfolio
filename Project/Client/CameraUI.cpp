#include "pch.h"
#include "CameraUI.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>

#include <Engine/CCamera.h>

CameraUI::CameraUI()
    : ComponentUI("Camera","##Camera", COMPONENT_TYPE::CAMERA)
{
}

CameraUI::~CameraUI()
{
}

void CameraUI::Activate()
{
    UI::Activate();

    m_camera = GetTargetObject()->Camera();
}

void CameraUI::render_update()
{
    ButtonTitle("Camera");

    ImGui::NewLine();
    static bool check = (bool)m_camera->GetProjType();
    if (ImGui::Checkbox("Orthographic", &check)) {
        if (check) {
            m_camera->SetProjType(PROJ_TYPE::PERSPECTIVE);
        }
        else {
            m_camera->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
        }
    }

    if (check) {
        static float fov = m_camera->GetFOV();
        if (ImGui::SliderFloat("FOV", &fov, 0.0f, XM_PI, "fov = %.3f")) {
            m_camera->SetFOV(fov);
        }
    }
    else {
        static float scale = m_camera->GetScale();
        if (ImGui::SliderFloat("Scale", &scale, 0.1f, 10, "scale = %.3f")) {
            m_camera->SetScale(scale);
        }
    }

    UINT layercheck = m_camera->GetLayerCheck();
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            auto layer = CLevelMgr::GetInst()->GetCurrentLevel()->GetLayer(i * 4 + j);
            if (layer == nullptr) continue;
            //if (layer->GetName() == L"") continue;
            string name = ToString(layer->GetName());
            if (name != L"") {
                name += "##nonameplayer";
            }
            name += std::to_string(i * 4 + j);

            bool lc = layercheck >> (i * 4 + j) & 1;
            if (ImGui::Checkbox(name.c_str(), &lc)) {
                m_camera->LayerCheck(i * 4 + j, lc);
            }
            ImGui::SameLine();
        }
        ImGui::NewLine();
    }

}
