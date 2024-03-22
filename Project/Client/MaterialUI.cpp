#include "pch.h"
#include "MaterialUI.h"

#include <Engine/CAssetMgr.h>
#include <Engine/CMaterial.h>
#include <Engine/CGraphicsShader.h>
#include <Engine/CTexture.h>

#include "ParamUI.h"
#include "../Engine/string.h"



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

	Ptr<CGraphicsShader> pShader = pMtrl->GetShader();
	string strShaderName;
	if (nullptr != pShader)
	{
		strShaderName = string(pShader->GetKey().begin(), pShader->GetKey().end());
	}

	ImGui::Text("Shader  ");
	ImGui::SameLine();
	ImGui::InputText("##ShaderName", (char*)strShaderName.c_str(), strShaderName.length(),
	                 ImGuiInputTextFlags_ReadOnly);


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


	string CheckboxKey = "";
	for (int i = 0; i < (int)TEX_PARAM::TEX_5; i++)
	{
		CheckboxKey = "TEX_";
		CheckboxKey += to_string(i);
		ImGui::Checkbox(CheckboxKey.c_str(), &_texarr[i]);
		
		if (_texarr[i])
		{
			string tempid = "##Mtrl Key";
			string tempparam = "##Mtrl param";
			tempid += to_string(i);
			tempparam += to_string(i);

			ImGui::Text("Key");
			ImGui::SameLine();
			ImGui::InputText(tempid.c_str(), inputkey[i], IM_ARRAYSIZE(inputkey[i])); // 입력 필드를 생성합니다.


			ImGui::Text("Param");
			ImGui::SameLine();
			ImGui::InputText(tempparam.c_str(), inputParam[i], IM_ARRAYSIZE(inputParam[i])); // 입력 필드를 생성합니다.


			string key = inputkey[i];
			string Texparam = inputParam[i];

			if (pMtrl->GetTexParam((TEX_PARAM)i) == nullptr)
			{
				Ptr<CTexture> temp = CAssetMgr::GetInst()->FindAsset<CTexture>(TempTextureKey);
				//pMtrl->SetTexParam(TEX_PARAM::TEX_0, temp);
				pMtrl->SetTexDesc((TEX_PARAM)i, TemTexStringParm);
			}
		}
		else
		{
			pMtrl->SetTexDesc((TEX_PARAM)i, "");
		}
	}


	//string CheckboxKey = "";
	//for(int i = 0; i<(int)TEX_PARAM::TEX_5; i++){
	//	CheckboxKey = "TEX_";
	//	CheckboxKey += std::to_string(i);
	//	ImGui::Checkbox(CheckboxKey.c_str(), &_texarr[i]);
	//	if (_texarr[i]) {

	//		static char inputKey[128] = ""; // 키을 받을 텍스트 버퍼
	//		static char inputParam[128] = ""; // 파라미터 스크립트을 받을 텍스트 버퍼

	//		ImGui::Text("Key");
	//		ImGui::SameLine();
	//		ImGui::InputText("##Mtrl Key", inputKey, IM_ARRAYSIZE(inputKey)); // 입력 필드를 생성합니다.


	//		ImGui::Text("Param");
	//		ImGui::SameLine();
	//		ImGui::InputText("##Param Key", inputParam, IM_ARRAYSIZE(inputParam)); // 입력 필드를 생성합니다.

	//		string key = inputKey;
	//		string Texparam = inputParam;

	//		if (pMtrl->GetTexParam((TEX_PARAM)i) == nullptr)
	//		{
	//			Ptr<CTexture> temp = CAssetMgr::GetInst()->FindAsset<CTexture>(TempTextureKey);
	//			pMtrl->SetTexParam(TEX_PARAM::TEX_0, temp);
	//			pMtrl->SetTexDesc((TEX_PARAM)i, TemTexStringParm);
	//		}
	//	}else{
	//		pMtrl->SetTexDesc((TEX_PARAM)i, "");
	//	}
	//}

}


void MaterialUI::SelectTexture(DWORD_PTR _dwData)
{
	string strTex = (char*)_dwData;
	wstring strTexName = ToWString(strTex);

	Ptr<CTexture> pTex = CAssetMgr::GetInst()->FindAsset<CTexture>(strTexName);
	Ptr<CMaterial> pMtrl = (CMaterial*)GetAsset().Get();
	pMtrl->SetTexParam(m_SelectTexParam, pTex);
}
