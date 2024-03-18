#pragma once
#include "ComponentUI.h"

class CSubAnimator2DUI;

class Animator2DUI :
    public ComponentUI
{
    virtual void render_update() override;

private:
    CSubAnimator2DUI* m_ChildDetailUI;

    CGameObject* pTarget;

    bool CheckRepeat = false;

public:
    CGameObject* GetTargetObj() { return pTarget; }

public:
    Animator2DUI();
    ~Animator2DUI();
};
