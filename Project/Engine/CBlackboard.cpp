#include "pch.h"
#include "CBlackboard.h"

#include "CGameObject.h"

void (*CBlackboard::SaveGameObject)( CGameObject* _Obj, ofstream& _fout) = nullptr;
CGameObject* (*CBlackboard::LoadGameObject)(ifstream& _fin) = nullptr;


CBlackboard::CBlackboard()
{
}

CBlackboard::CBlackboard(const CBlackboard& _board)
	: CEntity(_board)
	  , m_mapBBData()
{
}

CBlackboard::~CBlackboard()
{
}

void CBlackboard::AddBlackboardData(const wstring& _strKey, BB_DATA _Type, void* _Data)
{
	map<wstring, tBlackboardData>::iterator iter = m_mapBBData.find(_strKey);

	assert(iter == m_mapBBData.end());

	m_mapBBData.insert(make_pair(_strKey, tBlackboardData{_Type, _Data}));
}

void* CBlackboard::GetBlackboardData(const wstring& _strKey)
{
	map<wstring, tBlackboardData>::iterator iter = m_mapBBData.find(_strKey);

	if (iter == m_mapBBData.end())
		return nullptr;

	return iter->second.pData;
}

void CBlackboard::Save(ofstream& _fout)
{
	_fout << m_mapBBData.size() << endl;

	for (auto iter = m_mapBBData.begin(); iter != m_mapBBData.end(); ++iter)
	{
		_fout << ToString(iter->first) << endl;
		auto data = iter->second;

		_fout << (int)data.Type << endl;

		switch (data.Type)
		{
		case BB_DATA::INT:
			_fout << *((int*)data.pData) << endl;
			break;
		case BB_DATA::FLOAT:
			_fout << *((float*)data.pData) << endl;
			break;
		case BB_DATA::VEC2:
			_fout << *((Vec2*)data.pData) << endl;
			break;
		case BB_DATA::VEC3:
			_fout << *((Vec3*)data.pData) << endl;
			break;
		case BB_DATA::VEC4:
			_fout << *((Vec4*)data.pData) << endl;
			break;
		case BB_DATA::OBJECT:
			SaveGameObject((CGameObject*)data.pData, _fout);
			break;
		}
	
	}
}

void CBlackboard::Load(ifstream& _fin)
{
	int num;
	_fin >> num;

	for (int i =0; i < num; ++i)
	{
		string Desc;
		_fin >> Desc;

		int Type;
		_fin >> Type;

		tBlackboardData data;
		data.Type = (BB_DATA)Type;

		switch ((BB_DATA)Type)
		{
		case BB_DATA::INT:
			_fin >> *((int*)data.pData);
			break;
		case BB_DATA::FLOAT:
			_fin >> *((float*)data.pData);
			break;
		case BB_DATA::VEC2:
			_fin >> *((Vec2*)data.pData);
			break;
		case BB_DATA::VEC3:
			_fin >> *((Vec3*)data.pData);
			break;
		case BB_DATA::VEC4:
			_fin >> *((Vec4*)data.pData);
			break;
		case BB_DATA::OBJECT:
			data.pData = LoadGameObject(_fin);
			break;
		}
		AddBlackboardData(ToWString(Desc), data.Type, &data.pData);

	}
}
