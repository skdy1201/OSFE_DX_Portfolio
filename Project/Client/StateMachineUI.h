#pragma once
#include "ComponentUI.h"

class StateMachineUI :
    public ComponentUI
{
private:
    CStateMachine* m_stateMachine;
    Ptr<CFSM> m_FSM;
    map<wstring, class  CState*> m_States;
    vector<string> m_vecNames;

    int m_stateCount;
    int m_BlackBoardCnt;

public:
    void FSMSelect(DWORD_PTR _ptr);

public:
    virtual void render_update() override;
    virtual void Activate() override;

public:
    StateMachineUI();
    ~StateMachineUI();

private:
    //fsm ������
    void SelectFSM();
    //��Ϻ��� ���
    void Blackboard();
    //���� ������Ʈ ���
    void CurrentState();

    //������Ʈ ��� ��� + change state
    void StateList();
};

