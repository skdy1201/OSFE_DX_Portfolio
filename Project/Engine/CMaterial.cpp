#include "pch.h"
#include "CMaterial.h"

#include "CGraphicsShader.h"

#include "CDevice.h"
#include "CConstBuffer.h"
#include "CTexture.h"

#include "CPathMgr.h"

#include "Ptr.h"




CMaterial::CMaterial(bool _bEngine)
	: CAsset(ASSET_TYPE::MATERIAL, _bEngine)
	, m_Const{}
{
}

CMaterial::~CMaterial()
{
}

ofstream& operator<<(ofstream& _fout, tScalarParam _sout)
{
	_fout << (int)_sout.Type << endl;
	_fout << _sout.Desc << endl;

	return _fout;
}
ifstream& operator>>(ifstream& _fin, tScalarParam _sin)
{
	int num;
	_fin >> num >>_sin.Desc;

	_sin.Type = (SCALAR_PARAM)num;

	return _fin;

}


void CMaterial::SetTexDesc(TEX_PARAM _Param, const string& _desc)
{
	m_TexParam[(int)_Param] = _desc;
}

void CMaterial::UpdateData()
{	
	if (nullptr == m_pShader.Get())
		return;
	
	// 사용할 쉐이더 바인딩
	m_pShader->UpdateData();	

	// Texture Update(Register Binding)
	for (UINT i = 0; i < (UINT)TEX_PARAM::END; ++i)
	{
		if (nullptr != m_arrTex[i].Get())
		{
			m_arrTex[i]->UpdateData(i);
			m_Const.bTex[i] = 1;
		}
		else
		{
			CTexture::Clear(i);
			m_Const.bTex[i] = 0;
		}
	}

	// 상수 데이터 업데이트
	static CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::MATERIAL_CONST);
	pCB->SetData(&m_Const);
	pCB->UpdateData();	
}

void CMaterial::SetTexParam(TEX_PARAM _Param, Ptr<CTexture>_pTex)
{
	m_arrTex[(UINT)_Param] = _pTex;

}

void* CMaterial::GetScalarParam(SCALAR_PARAM _ParamType)
{
	switch (_ParamType)
	{
	case SCALAR_PARAM::INT_0:
	case SCALAR_PARAM::INT_1:
	case SCALAR_PARAM::INT_2:
	case SCALAR_PARAM::INT_3:
	{
		int idx = (UINT)_ParamType - (UINT)SCALAR_PARAM::INT_0;
		return m_Const.iArr + idx;
	}
		break;
	case SCALAR_PARAM::FLOAT_0:
	case SCALAR_PARAM::FLOAT_1:
	case SCALAR_PARAM::FLOAT_2:
	case SCALAR_PARAM::FLOAT_3:
	{
		int idx = (UINT)_ParamType - (UINT)SCALAR_PARAM::FLOAT_0;
		return m_Const.fArr + idx;
	}
		break;
	case SCALAR_PARAM::VEC2_0:
	case SCALAR_PARAM::VEC2_1:
	case SCALAR_PARAM::VEC2_2:
	case SCALAR_PARAM::VEC2_3:
	{
		int idx = (UINT)_ParamType - (UINT)SCALAR_PARAM::VEC2_0;
		return m_Const.v2Arr + idx;
	}	
		break;
	case SCALAR_PARAM::VEC4_0:
	case SCALAR_PARAM::VEC4_1:
	case SCALAR_PARAM::VEC4_2:
	case SCALAR_PARAM::VEC4_3:
	{
		int idx = (UINT)_ParamType - (UINT)SCALAR_PARAM::VEC4_0;
		return m_Const.v4Arr + idx;
	}
		break;
	case SCALAR_PARAM::MAT_0:
	case SCALAR_PARAM::MAT_1:
	case SCALAR_PARAM::MAT_2:
	case SCALAR_PARAM::MAT_3:
	{
		int idx = (UINT)_ParamType - (UINT)SCALAR_PARAM::MAT_0;
		return m_Const.matArr + idx;
	}
		break;
	}

	return nullptr;
}

int CMaterial::Save(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetContentPath();
	strFilePath += L"material\\";
	strFilePath += _strRelativePath;

	ofstream fout(strFilePath);

	if (!fout.is_open())
		return E_FAIL;
	string tempstr = "MtrlConst";
	fout << tempstr << endl;
	// 재질 상수값 저장
	fout << m_Const << endl;

	

	fout << "Scalar Param" << endl;
	// 재질 파라미터 값 저장
	vector<tScalarParam> temp = this->GetScalarParam();
	int scalarparamcount = temp.size();

	fout << scalarparamcount << endl;

	for(int i = 0; i < scalarparamcount; ++i)
	{
		fout << temp[i] << endl;
	}

	fout << "Tex Param" << endl;

	// 재질이 참조하는 텍스쳐 정보를 저장	
	for (UINT i = 0; i < (UINT)TEX_PARAM::END; ++i)
	{
		SaveAssetRef<CTexture>(m_arrTex[i], fout);
	}

	for (int i = 0; i < (int)TEX_PARAM::TEX_5 + 1; i++) {
		if (m_TexParam[i] == "") {
			fout << EMPTYSYMBOL << endl;
		}
		else {
			fout << m_TexParam[i] << endl;
		}
	}
	fout << endl;

	// 재질이 참조하는 쉐이더 정보를 저장
	SaveAssetRef<CGraphicsShader>(m_pShader, fout);

	return 0;
}

int CMaterial::Load(const wstring& _strFilePath)
{
	ifstream pFile(_strFilePath);

	if (!pFile.is_open())
		return E_FAIL;
	string temp;
	getline(pFile, temp);
	// 재질 상수값 저장
	pFile >> m_Const;

	// 재질 파라미터 값 저장
	int scalarparamcount = 0;
	while (getline(pFile, temp)) {
		if (temp != "" && temp !=" ")break;
	}

	pFile >> scalarparamcount;

	for(int i = 0; i < scalarparamcount; ++i)
	{
		int num;
		pFile >> num;

		SCALAR_PARAM tempScalar;
		tempScalar = (SCALAR_PARAM)num;

		string strTemp = "";
		while (getline(pFile, strTemp)) {
			if (strTemp != "")break;
		}

		this->AddScalarParam(tempScalar, strTemp);
	}

	while (getline(pFile, temp)) {
		if (temp != "")break;
	}

	// 재질이 참조하는 텍스쳐 정보를 로드
	for (UINT i = 0; i < (UINT)TEX_PARAM::END; ++i)
	{
		LoadAssetRef<CTexture>(m_arrTex[i], pFile);
	}

	for (int i = 0; i < (int)TEX_PARAM::TEX_5 + 1; i++) {
		string t;
		while(getline(pFile, t))
		{
			if (t != "") break;
		}
		m_TexParam[i] = t;
	}

	// 재질이 참조하는 쉐이더 정보를 저장
	LoadAssetRef<CGraphicsShader>(m_pShader, pFile);

	return 0;
}

void CheckSetTex(Ptr<CTexture> _texture[10], bool* texarr[(UINT)TEX_PARAM::END], TEX_PARAM eParam)
{
	UINT Curindex = (UINT)eParam;

	if(_texture != nullptr)
	{
		*texarr[Curindex] = true;
	}
	else
	{
		*texarr[Curindex] = false;
	}
	

}
