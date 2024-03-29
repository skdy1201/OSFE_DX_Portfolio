#pragma once
#include "CEntity.h"



class CFSM;
class CStateMachine;

class CState :
    public CEntity
{
private:
    UINT        m_iStateType;
	CFSM*       m_FSM;


public:
    virtual void finaltick() = 0;
    virtual void Enter() = 0;
    virtual void Exit() = 0;
    UINT GetStateType() { return m_iStateType; }

protected:
    void* GetBlackboardData(const wstring& _strKey);
    CFSM* GetFSM() { return m_FSM; }

    void ChangeState(const wstring& _strStateName);


    virtual void Save(ofstream& _fout);
    virtual void Load(ifstream& _fin);


public:
    CLONE_DISABLE(CState);

    CState();
    ~CState();

    friend class CFSM;
};
