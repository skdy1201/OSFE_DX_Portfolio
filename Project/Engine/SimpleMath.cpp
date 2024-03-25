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
               
