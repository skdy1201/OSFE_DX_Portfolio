#include "pch.h"
#include "CTileMap.h"

#include "CStructuredBuffer.h"

#include "CAssetMgr.h"
#include "CMesh.h"

#include "CTransform.h"

CTileMap::CTileMap()
	: CRenderComponent(COMPONENT_TYPE::TILEMAP)
	, m_FaceX(2)
	, m_FaceY(2)
	, m_vTileRenderSize(Vec2(128.f, 128.f))	
	, m_TileInfoBuffer(nullptr)
{
	SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"TileMapMtrl"));

	m_TileInfoBuffer = new CStructuredBuffer;

	SetFace(m_FaceX, m_FaceY);
}

CTileMap::CTileMap(const CTileMap& _OriginTileMap)
	: CRenderComponent(_OriginTileMap)
	, m_FaceX(_OriginTileMap.m_FaceX)
	, m_FaceY(_OriginTileMap.m_FaceY)
	, m_vTileRenderSize(_OriginTileMap.m_vTileRenderSize)	
	, m_TileAtlas(_OriginTileMap.m_TileAtlas)
	, m_vTilePixelSize(_OriginTileMap.m_vTilePixelSize)
	, m_vSliceSizeUV(_OriginTileMap.m_vSliceSizeUV)
	, m_MaxCol(_OriginTileMap.m_MaxCol)
	, m_MaxRow(_OriginTileMap.m_MaxRow)
	, m_vecTileInfo(_OriginTileMap.m_vecTileInfo)
	, m_TileInfoBuffer(nullptr)
{
	if (nullptr != _OriginTileMap.m_TileInfoBuffer)
	{
		m_TileInfoBuffer = _OriginTileMap.m_TileInfoBuffer->Clone();
	}	
}

CTileMap::~CTileMap()
{
	if (nullptr != m_TileInfoBuffer)
		delete m_TileInfoBuffer;
}

ofstream& operator<<(ofstream& _fout, tTileInfo& _tout)
{
	_fout << _tout.vLeftTopUV;
	_fout << endl;
	_fout << _tout.bRender << endl;
	_fout << _tout.padding;

	return _fout;
}

ifstream& operator>>(ifstream& _fout, tTileInfo& _tout)
{
	_fout >> _tout.vLeftTopUV;
	_fout >> _tout.bRender;
	_fout >> _tout.padding;

	return _fout;
}

void CTileMap::finaltick()
{
	// (타일 개수 * 타일 사이즈) 로 사이즈를 변경처리한다.
	Vec3 vTileMapSize = Vec3(m_FaceX * m_vTileRenderSize.x, m_FaceY * m_vTileRenderSize.y, 1.f);
	Transform()->SetRelativeScale(vTileMapSize);
}

void CTileMap::render()
{	
	// 재질에 아틀라스 텍스쳐 전달.
	GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, m_TileAtlas);
	
	// 타일의 가로 세로 개수
	GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, m_FaceX);
	GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_1, m_FaceY);
		
	// 아틀라스 이미지에서 타일 1개의 자르는 사이즈(UV 기준)
	GetMaterial()->SetScalarParam(SCALAR_PARAM::VEC2_0, m_vSliceSizeUV);

	// 각 타일 정보를 구조화 버퍼로 이동
	m_TileInfoBuffer->SetData(m_vecTileInfo.data(), m_vecTileInfo.size());

	// 타일 구조화 버퍼를 t20 에 바인딩
	m_TileInfoBuffer->UpdateData(20);

	// 재질 업데이트
	GetMaterial()->UpdateData();	

	Transform()->UpdateData();

	GetMesh()->render();
}


void CTileMap::UpdateData()
{

}


void CTileMap::SetTileAtlas(Ptr<CTexture> _Atlas, Vec2 _TilePixelSize)
{
	m_TileAtlas = _Atlas;
	m_vTilePixelSize = _TilePixelSize;

	m_MaxCol = m_TileAtlas->GetWidth() / (UINT)m_vTilePixelSize.x;
	m_MaxRow = m_TileAtlas->GetHeight() / (UINT)m_vTilePixelSize.y;

	m_vSliceSizeUV = Vec2(m_vTilePixelSize.x / m_TileAtlas->GetWidth()
		, m_vTilePixelSize.y / m_TileAtlas->GetHeight());
}

void CTileMap::SetFace(UINT _FaceX, UINT _FaceY)
{
	m_FaceX = _FaceX;
	m_FaceY = _FaceY;

	vector<tTileInfo> vecTemp;
	m_vecTileInfo.swap(vecTemp);
	m_vecTileInfo.resize(_FaceX * _FaceY);

	m_TileInfoBuffer->Create(sizeof(tTileInfo), _FaceX * _FaceY, SB_TYPE::READ_ONLY, true);
}

void CTileMap::SetTileIndex(UINT _Row, UINT _Col, UINT _ImgIdx)
{
	if (nullptr == m_TileAtlas)
		return;

	UINT idx = _Row* m_FaceX + _Col;

	// 렌더링할 타일 정보
	UINT iRow = _ImgIdx / m_MaxCol;
	UINT iCol = _ImgIdx % m_MaxCol;

	m_vecTileInfo[idx].vLeftTopUV = Vec2((iCol * m_vTilePixelSize.x) / m_TileAtlas->GetWidth()
								  , (iRow * m_vTilePixelSize.y) / m_TileAtlas->GetHeight());

	m_vecTileInfo[idx].bRender = 1;
}





void CTileMap::SaveToFile(ofstream& _fout)
{
	// TileMap 정보 저장
	_fout << m_FaceX << endl;
	_fout << m_FaceY << endl;
	_fout << m_vTileRenderSize << endl;

	SaveAssetRef(m_TileAtlas, _fout);

	_fout << m_vTilePixelSize << endl;
	_fout << m_vSliceSizeUV << endl;

	_fout << m_MaxCol << endl;
	_fout << m_MaxRow << endl;

	size_t InfoCount = m_vecTileInfo.size();
	_fout << InfoCount << endl;

	for (size_t i = 0; i < m_vecTileInfo.size(); i++)
	{
		_fout << m_vecTileInfo[i] << endl;
	}
}

void CTileMap::LoadFromFile(ifstream& _File)
{
	// TileMap 정보 저장
	_File >> m_FaceX;
	_File >> m_FaceY;
	_File >> m_vTileRenderSize;

	LoadAssetRef(m_TileAtlas, _File);

	_File >> m_vTilePixelSize;
	_File >> m_vSliceSizeUV;
	_File >> m_MaxCol;
	_File >> m_MaxRow;

	size_t InfoCount;
	_File >> InfoCount;


	m_vecTileInfo.resize(InfoCount);
	for (size_t i = 0; i < m_vecTileInfo.size(); i++)
	{
		_File >> m_vecTileInfo[i];
	}
}