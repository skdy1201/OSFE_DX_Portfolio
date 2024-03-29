#include "pch.h"
#include "CStateMgr.h"

#include "CTest.h"

void CStateMgr::GetStateInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CTest");
}

CState * CStateMgr::GetState(const wstring& _strStateName)
{
	if (L"CTest" == _strStateName)
		return new CTest;
	return nullptr;
}

CState * CStateMgr::GetState(UINT _iStateType)
{
	switch (_iStateType)
	{
	case (UINT)STATE_TYPE::TEST:
		return new CTest;
		break;
	}
	return nullptr;
}

const wchar_t * CStateMgr::GetStateName(CState * _pState)
{
	switch ((STATE_TYPE)_pState->GetStateType())
	{
	case STATE_TYPE::TEST:
		return L"CTest";
		break;

	}
	return nullptr;
}