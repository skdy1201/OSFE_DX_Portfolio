#include "pch.h"
#include "CStateMgr.h"

#include "CSniperIdleState.h"
#include "CSniperMoveState.h"

void CStateMgr::GetStateInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CSniperIdleState");
	_vec.push_back(L"CSniperMoveState");
}

CState * CStateMgr::GetState(const wstring& _strStateName)
{
	if (L"CSniperIdleState" == _strStateName)
		return new CSniperIdleState;
	if (L"CSniperMoveState" == _strStateName)
		return new CSniperMoveState;
	return nullptr;
}

CState * CStateMgr::GetState(UINT _iStateType)
{
	switch (_iStateType)
	{
	case (UINT)STATE_TYPE::SNIPERIDLESTATE:
		return new CSniperIdleState;
		break;
	case (UINT)STATE_TYPE::SNIPERMOVESTATE:
		return new CSniperMoveState;
		break;
	}
	return nullptr;
}

const wchar_t * CStateMgr::GetStateName(CState * _pState)
{
	switch ((STATE_TYPE)_pState->GetStateType())
	{
	case STATE_TYPE::SNIPERIDLESTATE:
		return L"CSniperIdleState";
		break;

	case STATE_TYPE::SNIPERMOVESTATE:
		return L"CSniperMoveState";
		break;

	}
	return nullptr;
}