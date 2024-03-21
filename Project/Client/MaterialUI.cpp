#include "pch.h"
#include "MaterialUI.h"

#include <Engine/CAssetMgr.h>
#include <Engine/CMaterial.h>
#include <Engine/CGraphicsShader.h>
#include <Engine/CTexture.h>

#include "ParamUI.h"

MaterialUI::MaterialUI()
	: AssetUI("Material", "##Material", ASSET_TYPE::MATERIAL)
	, m_CheckMaterial { false }
{
}

MaterialUI::~MaterialUI()
{
}


void MaterialUI::render_update()
{
	AssetUI::render_update();

    //받아 두기
    CMaterial* target = (CMaterial*)this->GetTargetAsset().Get();

    // 해당 텍스쳐 이미지 출력
    Ptr<CMaterial> pMtrl = (CMaterial*)GetAsset().Get();
    string strPath = string(pMtrl->GetRelativePath().begin(), pMtrl->GetRelativePath().end());

    string mtrlname = ToString(target->GetName());

    //이름 띄우고 입력하기
    char currentmtrlname[256];
    strcpy(currentmtrlname, mtrlname.c_str());
    ImGui::Text("Name : %s", currentmtrlname);

    if(ImGui::InputText("##input name", currentmtrlname, IM_ARRAYSIZE(currentmtrlname)))
    {
        mtrlname = currentmtrlname;
        target->SetName(ToWString(mtrlname));
    }

    ImGui::Text("Material");
    ImGui::SameLine();
    ImGui::InputText("##TexName", (char*)strPath.c_str(), strPath.length(), ImGuiInputTextFlags_ReadOnly);

    Ptr<CGraphicsShader> pShader = pMtrl->GetShader();
    string strShaderName;
    if (nullptr != pShader)
    {
        strShaderName = string(pShader->GetKey().begin(), pShader->GetKey().end());
    }

    ImGui::Text("Shader  ");
    ImGui::SameLine();
    ImGui::InputText("##ShaderName", (char*)strShaderName.c_str(), strShaderName.length(), ImGuiInputTextFlags_ReadOnly);
    

    ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
    ImGui::Text("Material Parameter");
    ImGui::Spacing(); ImGui::Spacing(); 

    ImGui::NewLine();
    ImGui::NewLine();

    bool IsSetTexture[9] = {};


    if (ImGui::CollapsingHeader("add texture param"))
    {
        if (ImGui::BeginTable("Add", 5))
        {
            make_Textable();
        }
    }

    

    // Shader Parameter
    if (nullptr == pShader)
        return;

    const vector<tScalarParam>& vecScalarParam = pShader->GetScalarParam();
    for (size_t i = 0; i < vecScalarParam.size(); ++i)
    {
        switch (vecScalarParam[i].Type)
        {
        case SCALAR_PARAM::INT_0:
        case SCALAR_PARAM::INT_1:
        case SCALAR_PARAM::INT_2:
        case SCALAR_PARAM::INT_3:                   
            ParamUI::Param_INT((int*)pMtrl->GetScalarParam(vecScalarParam[i].Type), vecScalarParam[i].Desc);
            break;
        case SCALAR_PARAM::FLOAT_0:
        case SCALAR_PARAM::FLOAT_1:
        case SCALAR_PARAM::FLOAT_2:
        case SCALAR_PARAM::FLOAT_3:
            ParamUI::Param_FLOAT((float*)pMtrl->GetScalarParam(vecScalarParam[i].Type), vecScalarParam[i].Desc);
            break;
        case SCALAR_PARAM::VEC2_0:
        case SCALAR_PARAM::VEC2_1:
        case SCALAR_PARAM::VEC2_2:
        case SCALAR_PARAM::VEC2_3:
            ParamUI::Param_VEC2((Vec2*)pMtrl->GetScalarParam(vecScalarParam[i].Type), vecScalarParam[i].Desc);
            break;
        case SCALAR_PARAM::VEC4_0:
        case SCALAR_PARAM::VEC4_1:
        case SCALAR_PARAM::VEC4_2:
        case SCALAR_PARAM::VEC4_3:
            ParamUI::Param_VEC4((Vec4*)pMtrl->GetScalarParam(vecScalarParam[i].Type), vecScalarParam[i].Desc);
            break;
        case SCALAR_PARAM::MAT_0:
        case SCALAR_PARAM::MAT_1:
        case SCALAR_PARAM::MAT_2:
        case SCALAR_PARAM::MAT_3:
            break;        
        }        
    }

    const vector<tTexParam>& vecTexParam = pShader->GetTexParam();
    for (size_t i = 0; i < vecTexParam.size(); ++i)
    {
        Ptr<CTexture> pTex = pMtrl->GetTexParam(vecTexParam[i].Type);      
        if (ParamUI::Param_TEXTURE(pTex, vecTexParam[i].Desc, this, (Delegate_1)&MaterialUI::SelectTexture))
        {           
            // 리스트 버튼을 눌렀다면
            m_SelectTexParam = vecTexParam[i].Type;
        }
        pMtrl->SetTexParam(vecTexParam[i].Type, pTex);
    }
}

void MaterialUI::make_Textable()
{
    ImGui::TableNextColumn();
	if(ImGui::Checkbox("TEX_0", m_CheckMaterial))
	{
		
	}
    ImGui::TableNextColumn(); ImGui::Checkbox("TEX_1", &m_CheckMaterial[1]);
    ImGui::TableNextColumn(); ImGui::Checkbox("TEX_2", &m_CheckMaterial[2]);
    ImGui::TableNextColumn(); ImGui::Checkbox("TEX_3", &m_CheckMaterial[3]);
    ImGui::TableNextColumn(); ImGui::Checkbox("TEX_4", &m_CheckMaterial[4]);
    ImGui::TableNextColumn(); ImGui::Checkbox("TEX_5", &m_CheckMaterial[5]);
    ImGui::TableNextColumn(); ImGui::Checkbox("TEXCUBE_0", &m_CheckMaterial[6]);
    ImGui::TableNextColumn(); ImGui::Checkbox("TEXCUBE_1", &m_CheckMaterial[7]);
    ImGui::TableNextColumn(); ImGui::Checkbox("TEXARR_0", &m_CheckMaterial[8]);
    ImGui::TableNextColumn(); ImGui::Checkbox("TEXARR_1", &m_CheckMaterial[9]);
    ImGui::EndTable();
}

void MaterialUI::SelectTexture(DWORD_PTR _dwData)
{
    string strTex = (char*)_dwData;
    wstring strTexName = ToWString(strTex);

    Ptr<CTexture> pTex = CAssetMgr::GetInst()->FindAsset<CTexture>(strTexName);
    Ptr<CMaterial> pMtrl = (CMaterial*)GetAsset().Get();
    pMtrl->SetTexParam(m_SelectTexParam, pTex);    
}
