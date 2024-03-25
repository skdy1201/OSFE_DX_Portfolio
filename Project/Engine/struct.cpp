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