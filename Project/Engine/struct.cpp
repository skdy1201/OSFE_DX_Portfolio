#include "pch.h"
#include "struct.h"

ofstream& operator<<(ofstream& _fout, tLightInfo& m_Info)
{
	_fout << m_Info.vColor << endl;
	_fout << m_Info.vSpecular << endl;
	_fout << m_Info.vAmbient << endl;
	_fout << m_Info.vWorldPos << endl;
	_fout << m_Info.vWorldDir << endl;
	_fout << m_Info.fRadius << endl;
	_fout << m_Info.fAngle << endl;
	_fout << m_Info.LightType << endl;
	_fout << m_Info.vPadding << endl;

	return _fout;
}


ifstream& operator>>(ifstream& _fout, tLightInfo& m_Info)
{
	_fout >> m_Info.vColor;
	_fout >> m_Info.vSpecular;
	_fout >> m_Info.vAmbient;
	_fout >> m_Info.vWorldPos;
	_fout >> m_Info.vWorldDir;
	_fout >> m_Info.fRadius;
	_fout >> m_Info.fAngle;
	_fout >> m_Info.LightType;
	_fout >> m_Info.vPadding;

	return _fout;
}

ofstream& operator<<(ofstream& fout, tMtrlConst& mtrl)
{
	for (int i = 0; i < 4; i++) {
		fout << mtrl.iArr[i] << " ";
	}
	for (int i = 0; i < 4; i++) {
		fout << mtrl.fArr[i] << " ";
	}
	for (int i = 0; i < 4; i++) {
		fout << mtrl.v2Arr[i] << " ";
	}
	for (int i = 0; i < 4; i++) {
		fout << mtrl.v4Arr[i] << " ";
	}
	fout << endl;
	for (int i = 0; i < 4; i++) {
		fout << mtrl.matArr[i] << " ";
	}
	fout << endl;
	for (int i = 0; i < (UINT)TEX_PARAM::END; i++) {
		fout << mtrl.bTex[i] << " ";
	}
	fout << endl;
	return fout;

}

ifstream& operator>>(ifstream& fin, tMtrlConst& mtrl)
{
	for (int i = 0; i < 4; i++) {
		fin >> mtrl.iArr[i];
	}
	for (int i = 0; i < 4; i++) {
		fin >> mtrl.fArr[i];
	}
	for (int i = 0; i < 4; i++) {
		fin >> mtrl.v2Arr[i];
	}
	for (int i = 0; i < 4; i++) {
		fin >> mtrl.v4Arr[i];
	}
	for (int i = 0; i < 4; i++) {
		fin >> mtrl.matArr[i];
	}

	for (int i = 0; i < (UINT)TEX_PARAM::END; i++) {
		fin >> mtrl.bTex[i];
	}

	return fin;

}