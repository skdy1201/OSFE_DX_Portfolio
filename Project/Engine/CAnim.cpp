#include "pch.h"
#include "CAnim.h"

#include "CTimeMgr.h"

#include "CDevice.h"
#include "CConstBuffer.h"

CAnim::CAnim()
	: m_Animator(nullptr)
	, m_CurFrmIdx(0)
	, m_bFinish(false)
	, m_AccTime(0.f)
{
}

CAnim::CAnim(const CAnim& _OriginAnim)
	: CEntity(_OriginAnim)
	, m_Animator(nullptr)
	, m_vecFrm(_OriginAnim.m_vecFrm)
	, m_CurFrmIdx(_OriginAnim.m_CurFrmIdx)
	, m_bFinish(_OriginAnim.m_bFinish)
	, m_AtlasTex(_OriginAnim.m_AtlasTex)
	, m_AccTime(_OriginAnim.m_AccTime)
{
}

CAnim::~CAnim()
{
}

ofstream& operator<<(ofstream& fout, tAnimFrm& anim)
{
	fout << anim.vLeftTop << endl;
	fout << anim.vSlice << endl;
	fout << anim.vOffset << endl;
	fout << anim.vBackground << endl;
	fout << anim.Duration;

	return fout;
}

ifstream& operator>>(ifstream& _fout, tAnimFrm& _anim)
{
	_fout >> _anim.vLeftTop;
	_fout >> _anim.vSlice;
	_fout >> _anim.vOffset;
	_fout >> _anim.vBackground;
	_fout >> _anim.Duration;

	return _fout;
}

void CAnim::finaltick()
{	
	m_AccTime += DT;

	if (m_vecFrm[m_CurFrmIdx].Duration < m_AccTime)
	{
		++m_CurFrmIdx;
		if (m_vecFrm.size() <= m_CurFrmIdx)
		{
			m_CurFrmIdx = (int)m_vecFrm.size() - 1;
			m_bFinish = true;
		}
		m_AccTime = 0.f;
	}
}

void CAnim::UpdateData()
{
	// 현재 프레임 정보를 상수버퍼로 옮기고 b2 레지스터로 바인딩
	static CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::ANIM2D_DATA);
	tAnimData2D data = {};
	data.UseAnim2D = 1;
	data.vLeftTop = m_vecFrm[m_CurFrmIdx].vLeftTop;
	data.vOffset = m_vecFrm[m_CurFrmIdx].vOffset;
	data.vSlizeSize = m_vecFrm[m_CurFrmIdx].vSlice;
	data.vBackGround = m_vecFrm[m_CurFrmIdx].vBackground;

	pCB->SetData(&data);
	pCB->UpdateData();

	// 아틀라스 텍스쳐 t10 에 바인딩
	m_AtlasTex->UpdateData(10);
}

void CAnim::Clear()
{
	static CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::ANIM2D_DATA);
	tAnimData2D data = {};
	data.UseAnim2D = 0;

	pCB->SetData(&data);
	pCB->UpdateData();
}

void CAnim::Create(CAnimator2D* _Animator, Ptr<CTexture> _Atlas, Vec2 _vLeftTop
	, Vec2 _vSliceSize, Vec2 _vOffset, Vec2 _vBackground, int _FrmCount, float _FPS)
{
	m_Animator = _Animator;
	m_AtlasTex = _Atlas;

	for (int i = 0; i < _FrmCount; ++i)
	{
		tAnimFrm frm = {};
				
		frm.vSlice = Vec2(_vSliceSize.x / (float)_Atlas->GetWidth(), _vSliceSize.y / (float)_Atlas->GetHeight());

		frm.vLeftTop = Vec2(_vLeftTop.x / (float)_Atlas->GetWidth() + frm.vSlice.x * i, _vLeftTop.y / (float)_Atlas->GetHeight());

		frm.vOffset = Vec2(_vOffset.x / (float)_Atlas->GetWidth(), _vOffset.y / (float)_Atlas->GetHeight());
		frm.Duration = 1.f / _FPS;

		frm.vBackground = Vec2(_vBackground.x / (float)_Atlas->GetWidth(), _vBackground.y / (float)_Atlas->GetHeight());
	

		m_vecFrm.push_back(frm);
	}
}

void CAnim::SaveToFile(ofstream& _fout)
{
	// 애니메이션 이름 저장
	_fout << GetName() << endl;
	
	// 모든 프레임 정보 저장
	size_t FrmSize = m_vecFrm.size();

	_fout << FrmSize << endl;

	for(int i = 0; i < FrmSize; ++i)
	{
		_fout << m_vecFrm[i] << endl;

	}

	// 애니메이션이 참조하던 텍스쳐 정보 저장
	SaveAssetRef(m_AtlasTex, _fout);
}

void CAnim::LoadFromFile(ifstream& _File)
{
	// 애니메이션 이름 로드
	string strName;
	_File >> strName;
	SetName(strName);
	
	// 모든 프레임 정보 로드
	size_t FrmSize = 0;
	_File >> FrmSize;
	m_vecFrm.resize(FrmSize);
	
	for (int i = 0 ; i < FrmSize; ++i)
	{
		_File >> m_vecFrm[i];
	}
	
	// 애니메이션이 참조하던 텍스쳐 정보 로드
	LoadAssetRef(m_AtlasTex, _File);
}
