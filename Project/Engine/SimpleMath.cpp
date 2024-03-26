#include "pch.h"
#include "SimpleMath.h"

ofstream& DirectX::SimpleMath::operator<<(ofstream& _fout, Vector2& _vout)
{
    _fout << _vout.x << " " << _vout.y;
    return _fout;
}

ifstream& SimpleMath::operator>>(ifstream& fin, Vector2& vec)
{
    fin >> vec.x >> vec.y;
    return fin;
}

ofstream& DirectX::SimpleMath::operator<<(ofstream& _fout, Vector3& _vout)
{
    _fout << _vout.x << " " << _vout.y << " " << _vout.z;
    return _fout;
}

ifstream& SimpleMath::operator>>(ifstream& _fin, Vector3& _vin)
{
    _fin >> _vin.x >> _vin.y >> _vin.z;
    return _fin;
}

ofstream& DirectX::SimpleMath::operator<<(ofstream& _fout, Vector4& _vout)
{
    _fout << _vout.x << " " << _vout.y << " " << _vout.w << " " << _vout.z;
    return _fout;
}

ifstream& SimpleMath::operator>>(ifstream& _fin, Vector4& _vin)
{
    _fin >> _vin.x >> _vin.y >> _vin.w >> _vin.z;
    return _fin;
}
               

ofstream& DirectX::SimpleMath::operator<<(ofstream& _fout, Matrix& matrix)
{
    _fout << matrix._11 << " " << matrix._12 << " " << matrix._13 << " " << matrix._14 << " " << endl;
    _fout << matrix._21 << " " << matrix._22 << " " << matrix._23 << " " << matrix._24 << " " << endl;
    _fout << matrix._31 << " " << matrix._32 << " " << matrix._33 << " " << matrix._34 << " " << endl;
    _fout << matrix._41 << " " << matrix._42 << " " << matrix._43 << " " << matrix._44 << " " << endl;
    return _fout;

}

ifstream& DirectX::SimpleMath::operator>>(ifstream& _fin, Matrix& matrix)
{
    _fin >> matrix._11 >> matrix._12 >> matrix._13 >> matrix._14;
    _fin >> matrix._21 >> matrix._22 >> matrix._23 >> matrix._24;
    _fin >> matrix._31 >> matrix._32 >> matrix._33 >> matrix._34;
    _fin >> matrix._41 >> matrix._42 >> matrix._43 >> matrix._44;
    return _fin;

}