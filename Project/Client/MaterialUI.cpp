#include "pch.h"
#include "MaterialUI.h"

#include <Engine/CAssetMgr.h>
#include <Engine/CMaterial.h>
#include <Engine/CGraphicsShader.h>
#include <Engine/CTexture.h>

#include "ParamUI.h"

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

	if(target != currentMtrl)
	{
		prevMtrl = currentMtrl;
		currentMtrl = target;
	}

	

	// 해당 텍스쳐 이미지 출력
	Ptr<CMaterial> pMtrl = (CMaterial*)GetAsset().Get();
	string strPath = string(pMtrl->GetRelativePath().begin(), pMtrl->GetRelativePath().end());

	string mtrlname = ToString(target->GetName());

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

	const vector<tTexParam>& vecTexParam = pMtrl->GetTexParam();
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

void MaterialUI::make_Textable(bool* _texarr, Ptr<CMaterial>& pMtrl)
{
	vector<tTexParam> temp = pMtrl.Get()->GetTexParam();

	


	fill_n(_texarr, static_cast<size_t>(TEX_PARAM::END), false);

	if(pMtrl != nullptr && this->currentMtrl != prevMtrl)
	{
		for (int i = 0; i < temp.size(); ++i)
		{
			switch (temp[i].Type)
			{
			case TEX_PARAM::TEX_0:
				_texarr[0] = true;
				break;
			case TEX_PARAM::TEX_1:
				_texarr[1] = true;
				break;
			case TEX_PARAM::TEX_2:
				_texarr[2] = true;
				break;
			case TEX_PARAM::TEX_3:
				_texarr[3] = true;
				break;
			case TEX_PARAM::TEX_4:
				_texarr[4] = true;
				break;
			case TEX_PARAM::TEX_5:
				_texarr[5] = true;
				break;
			case TEX_PARAM::TEXCUBE_0:
				_texarr[6] = true;
				break;
			case TEX_PARAM::TEXCUBE_1:
				_texarr[7] = true;
				break;
			case TEX_PARAM::TEXARR_0:
				_texarr[8] = true;
				break;
			case TEX_PARAM::TEXARR_1:
				_texarr[9] = true;
				break;
			case TEX_PARAM::END:
				break;
			}
		}
	}


		ImGui::TableNextColumn();
		if (ImGui::Checkbox("TEX_0", _texarr))
		{
		
		}

		ImGui::TableNextColumn();
		if(ImGui::Checkbox("TEX_1", &_texarr[1]))
		{
			if (pMtrl->GetTexParam(TEX_PARAM::TEX_1) == nullptr)
			{
				Ptr<CTexture> temp = CAssetMgr::GetInst()->CreateTexture(L"tempTEX_0", 1, 1, DXGI_FORMAT_R8G8B8A8_UNORM,
					D3D11_BIND_SHADER_RESOURCE);

				pMtrl->AddTexParam(TEX_PARAM::TEX_0, "temp");
				*_texarr = true;
			}
		}

		ImGui::TableNextColumn();
		if(ImGui::Checkbox("TEX_2", &_texarr[2]))
		{

		}
		ImGui::TableNextColumn();
		ImGui::Checkbox("TEX_3", &_texarr[3]);
		ImGui::TableNextColumn();
		ImGui::Checkbox("TEX_4", &_texarr[4]);
		ImGui::TableNextColumn();
		ImGui::Checkbox("TEX_5", &_texarr[5]);
		ImGui::TableNextColumn();
		ImGui::Checkbox("TEXCUBE_0", &_texarr[6]);
		ImGui::TableNextColumn();
		ImGui::Checkbox("TEXCUBE_1", &_texarr[7]);
		ImGui::TableNextColumn();
		ImGui::Checkbox("TEXARR_0", &_texarr[8]);
		ImGui::TableNextColumn();
		ImGui::Checkbox("TEXARR_1", &_texarr[9]);

		
	ImGui::EndTable();
}

void MaterialUI::AddTexture(Ptr<CMaterial> _mtrl,TEX_PARAM _Param, wstring Key, string paramname, bool* _arr ,UINT barrnum)
{
	if (_mtrl->GetTexParam(_Param) == nullptr)
	{
		Ptr<CTexture> temp = CAssetMgr::GetInst()->CreateTexture(Key, 1, 1, DXGI_FORMAT_R8G8B8A8_UNORM,
			D3D11_BIND_SHADER_RESOURCE);

		_mtrl->AddTexParam(_Param, paramname);

		_arr[barrnum];
	}
}

void MaterialUI::SelectTexture(DWORD_PTR _dwData)
{
	string strTex = (char*)_dwData;
	wstring strTexName = ToWString(strTex);

	Ptr<CTexture> pTex = CAssetMgr::GetInst()->FindAsset<CTexture>(strTexName);
	Ptr<CMaterial> pMtrl = (CMaterial*)GetAsset().Get();
	pMtrl->SetTexParam(m_SelectTexParam, pTex);
}
