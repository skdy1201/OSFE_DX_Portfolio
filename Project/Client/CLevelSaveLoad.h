#pragma once


class CLevel;
class CLayer;
class CGameObject;

class CLevelSaveLoad
{
public:
	static void SaveLevel(CLevel* _Level, const wstring& _strLevelPath);

	static void SaveLayer(CLayer* _Layer, ofstream&_File);

	static void SaveGameObject(CGameObject* _Obj, ofstream& _File);

	static CLevel* LoadLevel(const wstring& _strLevelPath);
	static void LoadLayer(CLayer* _Layer, ifstream& _File);
	static CGameObject* LoadGameObject(ifstream& _File);
};

