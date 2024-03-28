#include "pch.h"
#include "CAnimator2D.h"

#include "CAnim.h"

CAnimator2D::CAnimator2D()
	: CComponent(COMPONENT_TYPE::ANIMATOR2D)
{

}

CAnimator2D::CAnimator2D(const CAnimator2D& _OriginAnimator)
	: CComponent(_OriginAnimator)
	, m_CurAnim(nullptr)
	, m_bRepeat(_OriginAnimator.m_bRepeat)
{
	map<wstring, CAnim*>::const_iterator iter = _OriginAnimator.m_mapAnim.begin();
	for (; iter != _OriginAnimator.m_mapAnim.end(); ++iter)
	{
		CAnim* pCloneAnim = iter->second->Clone();

		pCloneAnim->m_Animator = this;
		m_mapAnim.insert(make_pair(iter->first, pCloneAnim));
	}

	if (nullptr != _OriginAnimator.m_CurAnim)
	{
		m_CurAnim = FindAnim(_OriginAnimator.m_CurAnim->GetName());
	}
}

CAnimator2D::~CAnimator2D()
{
	Delete_Map(m_mapAnim);	
}

void CAnimator2D::finaltick()
{
	if (nullptr == m_CurAnim)
		return;

	if (m_CurAnim->IsFinish() && m_bRepeat)
	{
		m_CurAnim->Reset();
	}

	m_CurAnim->finaltick();
}

void CAnimator2D::UpdateData()
{
	if (nullptr == m_CurAnim)
		return;

	m_CurAnim->UpdateData();
}

void CAnimator2D::Clear()
{	
	CAnim::Clear();
}

void CAnimator2D::Create(const wstring& _strKey, Ptr<CTexture> _AltasTex, Vec2 _LeftTop
	, Vec2 _vSliceSize, Vec2 _OffsetSize, Vec2 _Background, int _FrmCount, float _FPS)
{
	CAnim* pAnim = FindAnim(_strKey);
	assert(!pAnim);

	pAnim = new CAnim;	
	pAnim->Create(this, _AltasTex, _LeftTop, _vSliceSize, _OffsetSize, _Background, _FrmCount, _FPS);
	pAnim->SetName((_strKey));
	m_mapAnim.insert(make_pair(_strKey, pAnim));
}

void CAnimator2D::Create(const wstring& _strKey, CAnim* Anim)
{

	CAnim* pAnim = FindAnim(_strKey);
	assert(!pAnim);

	Anim->SetName((_strKey));
	m_mapAnim.insert(make_pair(_strKey, Anim));
	
}

void CAnimator2D::AddAnimtoMap(CAnim* _Anim)
{
	m_mapAnim.insert(make_pair(_Anim->GetName(), _Anim));
}

CAnim* CAnimator2D::FindAnim(const wstring& _strKey)
{
	map<wstring, CAnim*>::iterator iter = m_mapAnim.find(_strKey);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

void CAnimator2D::Play(const wstring& _strAnimName, bool _bRepeat)
{
	CAnim* pAnim = FindAnim(_strAnimName);
	if (nullptr == pAnim)
		return;

	m_bRepeat = _bRepeat;

	m_CurAnim = pAnim;
	m_CurAnim->Reset();
}

void CAnimator2D::SaveToFile(ofstream& _fout)
{
	// 애니메이션 개수 저장
	size_t AnimCount = m_mapAnim.size();
	_fout << AnimCount << endl;

	for (const auto& pair : m_mapAnim)
	{
		pair.second->SaveToFile(_fout);
	}
	
}

void CAnimator2D::LoadFromFile(ifstream& _File)
{
	// 애니메이션 개수 로드
	size_t AnimCount = 0;
	_File >> AnimCount;
		
	for (size_t i = 0; i < AnimCount; ++i)
	{
		CAnim* pAnim = new CAnim;
		pAnim->LoadFromFile(_File);

		pAnim->m_Animator = this;
		m_mapAnim.insert(make_pair(pAnim->GetName(), pAnim));		
	}
}
