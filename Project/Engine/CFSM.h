#pragma once
#include "CAsset.h"

#include "CState.h"
#include "CBlackboard.h"

class CStateMachine;

class CFSM :
    public CAsset
{
private:
    CFSM*                   m_Master;
    CStateMachine*          m_StateMachie; // FSM �� ����ϴ� StateMachine;

    map<wstring, CState*>   m_mapState;
    CBlackboard*            m_Blackboard;

    CState*                 m_CurState;

public:
    void AddState(const wstring& _StateName, CState* _State);

    CState* FindState(const wstring& _StateName);

    void SetState(const wstring& _strState);

    void SetStateMachine(CStateMachine* _SM)
    { 
        if (m_Master) 
        { 
            m_StateMachie = _SM; 
        } 
    }

    CFSM* GetFSMIstance();
    CState* GetCurState() { return m_CurState; }


    CStateMachine* GetStateMachine() { return m_StateMachie; }

    void ChangeState(const wstring& _strStateName);

public:
    void finaltick();


    virtual int Save(const wstring& _strRelativePath);

    virtual int Load(const wstring& _strFilePath);


    static CState* (*LoadStateFunc)(const string& _strFilePath);

public:
    CLONE_DISABLE(CFSM);
    CFSM(bool _bEngine = false);    
    ~CFSM();

private:
    map<wstring, CState*>& GetStates() { return m_mapState; }
    friend class StateMachineUI;
    friend class FSMUI;
};

