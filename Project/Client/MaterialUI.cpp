#include "pch.h"
#include "MaterialUI.h"

#include <Engine/CAssetMgr.h>
#include <Engine/CMaterial.h>
#include <Engine/CGraphicsShader.h>
#include <Engine/CTexture.h>

#include "ParamUI.h"
#include "../Engine/string.h"
#include "ListUI.h"



MaterialUI::MaterialUI()
	: AssetUI("Material", "##Material", ASSET_TYPE::MATERIAL)
	  , m_CheckMaterial{false}
	  , currentMtrl(nullptr)
	  , prevMtrl(nullptr)
{
}

MaterialUI::~MaterialUI()
{
}


void MaterialUI::render_update()
{
	AssetUI::render_update();


	//받아 두기
	Ptr<CMaterial> target = (CMaterial*)this->GetTargetAsset().Get();

	prevMtrl = currentMtrl;
	m_IsChange = false;

	if(target != currentMtrl)
	{
		currentMtrl = target;
		m_IsChange = true;
		
	}

	

	// 해당 텍스쳐 이미지 출력
	Ptr<CMaterial> pMtrl = (CMaterial*)GetAsset().Get();
	string strPath = string(pMtrl->GetRelativePath().begin(), pMtrl->GetRelativePath().end());

	

	string mtrlname = ToString(currentMtrl->GetName());

	//이름 띄우고 입력하기
	char currentmtrlname[256];
	strcpy(currentmtrlname, mtrlname.c_str());
	ImGui::Text("Name : %s", currentmtrlname);
	
	if (ImGui::InputText("##input name", currentmtrlname, IM_ARRAYSIZE(currentmtrlname)))
	{
		mtrlname = currentmtrlname;
		target->SetName(ToWString(mtrlname));
	}

	ImGui::Text("Material");
	ImGui::SameLine();
	ImGui::InputText("##TexName", (char*)strPath.c_str(), strPath.length(), ImGuiInputTextFlags_ReadOnly);

	ImGui::Text("Shader");
	ImGui::SameLine();

	if (pMtrl->GetShader() != nullptr)
	{
		string shaderstring = ToString(pMtrl->GetShader()->GetName());
		ImGui::InputText("##inputshader", (char*)shaderstring.c_str(), shaderstring.length(), ImGuiInputTextFlags_ReadOnly);
	}

	ImGui::SameLine();
	if(ImGui::Button("##Input Shader", ImVec2{ 20, 20 }))
	{
		Ptr< CGraphicsShader> pShader = target.Get()->GetShader();

		if(pShader == nullptr)
		{
			// 리스트 UI
			ListUI* pListUI = (ListUI*)CImGuiMgr::GetInst()->FindUI("##List");

			vector<string> vecShaderName;
			CAssetMgr::GetInst()->GetAssetName(ASSET_TYPE::GRAPHICS_SHADER, vecShaderName);

			pListUI->AddString(vecShaderName);
			pListUI->SetDbClickDelegate(this, (Delegate_1)&MaterialUI::ShaderSelect);
			pListUI->Activate();
		}



	}


	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Text("Material Parameter");
	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::NewLine();
	ImGui::NewLine();

	bool IsSetTexture[9] = {};

	if(ImGui::Button("Save", ImVec2{ 50.f, 50.f }))
	{
		mtrlname += ".mtrl";
		currentMtrl->Save(ToWString(mtrlname));
	}


	if (ImGui::CollapsingHeader("add texture param"))
	{
		if (ImGui::BeginTable("Add", 5))
		{
			make_Textable(m_CheckMaterial, target);

			ImGui::EndTable();
		}
	}


	// material Parameter
	if (nullptr == pMtrl)
		return;



	const vector<tScalarParam>& vecScalarParam = pMtrl->GetScalarParam();
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

	

	for (size_t i = 0; i < (int)TEX_PARAM::END; ++i)
	{
		const string& TexDesc = pMtrl->GetTexDesc(i);

		if(TexDesc == ""){
			continue;
		}

		Ptr<CTexture> pTex = pMtrl->GetTexParam((TEX_PARAM)i);

		if (ParamUI::Param_TEXTURE(pTex, TexDesc, this, (Delegate_1)&MaterialUI::SelectTexture))
		{
			// 리스트 버튼을 눌렀다면
			m_SelectTexParam = (TEX_PARAM)i;
		}
		pMtrl->SetTexParam((TEX_PARAM)i, pTex);
	}
}

void MaterialUI::make_Textable(bool* _texarr, Ptr<CMaterial>& pMtrl)
{

	// Detect & Change
	if (pMtrl != nullptr && m_IsChange)
	{
		fill_n(_texarr, static_cast<size_t>(TEX_PARAM::END), false);

		for (size_t i = 0; i < (int)TEX_PARAM::END; ++i)
		{
			const string& TexDesc = pMtrl->GetTexDesc(i);

			if (TexDesc != "") {
				_texarr[i] = true;
			}
		}
	}


	ImGui::TableNextColumn();

	//체크 이후, desc가 달라지면 desc 갱신
	string CheckboxKey = "";
	for (int i = 0; i < (int)TEX_PARAM::TEX_5; i++)
	{
		CheckboxKey = "TEX_";
		CheckboxKey += to_string(i);
		ImGui::Checkbox(CheckboxKey.c_str(), &_texarr[i]);
		
		if (_texarr[i])
		{
			string tempparam = "##Mtrl param";
			tempparam += to_string(i);

			ImGui::Text("Param");
			ImGui::SameLine();
			ImGui::InputText(tempparam.c_str(), inputParam[i], IM_ARRAYSIZE(inputParam[i])); // 입력 필드를 생성합니다.

			string Texparam = inputParam[i];

			if(pMtrl->GetTexDesc((TEX_PARAM)i) == "")
			{
				pMtrl->SetTexDesc((TEX_PARAM)i, TemTexStringParm);
			}
			

			//해당 texture 자리가 비어있지 않다면 desc바꿔주기
			if(pMtrl.Get()->GetTexParam((TEX_PARAM)i) != nullptr)
			{
				Check_ChangeDesc(pMtrl, (TEX_PARAM)i, inputParam[i]);
			}
		}
		else
		{
			pMtrl->SetTexDesc((TEX_PARAM)i, "");
		}
	}

	


}

void MaterialUI::Check_ChangeDesc(Ptr<CMaterial>& _Curmtrl, TEX_PARAM _CurrentTexParam, string _ChangeDesc)
{
	Ptr<CMaterial> CurrentMtrl = _Curmtrl;
	string changedesc = " ";

	changedesc = CurrentMtrl->GetTexDesc(_CurrentTexParam);

	if(_ChangeDesc != "" && changedesc != _ChangeDesc)
	{
		CurrentMtrl->SetTexDesc(_CurrentTexParam, _ChangeDesc);
	}
}

void MaterialUI::ShaderSelect(DWORD_PTR _ptr)
{
	string strshader = (char*)_ptr;
	wstring strshaderName = ToWString(strshader);

	Ptr<CGraphicsShader> pshader = CAssetMgr::GetInst()->FindAsset<CGraphicsShader>(strshaderName);

	Ptr<CMaterial> target = dynamic_cast<CMaterial*>(GetTargetAsset().Get());
	target->SetShader(pshader);
}


void MaterialUI::SelectTexture(DWORD_PTR _dwData)
{
	string strTex = (char*)_dwData;
	wstring strTexName = ToWString(strTex);

	Ptr<CTexture> pTex = CAssetMgr::GetInst()->FindAsset<CTexture>(strTexName);
	Ptr<CMaterial> pMtrl = (CMaterial*)GetAsset().Get();
	pMtrl->SetTexParam(m_SelectTexParam, pTex);
}
