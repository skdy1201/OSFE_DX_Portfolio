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
    //fsm 선택지
    void SelectFSM();
    //블록보드 출력
    void Blackboard();
    //현재 스테이트 출력
    void CurrentState();

    //스테이트 목록 출력 + change state
    void StateList();
};

