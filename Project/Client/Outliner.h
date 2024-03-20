#pragma once
#include "UI.h"

#include <Engine/CComponent.h>
// 현재 레벨에 있는 모든 오브젝트들 나열

class TreeUI;
class TreeNode;

class Outliner :
    public UI
{
private:
    TreeUI*     m_Tree;


public:
    virtual void render_update() override;
	TreeUI* GetTree() { return m_Tree; }

public:
    void ResetCurrentLevel();

private:
    void AddObjectToTree(TreeNode* _Node, CGameObject* _Object);

	void SelectObject(DWORD_PTR _Node);

    void DragDropObject(DWORD_PTR _Dest, DWORD_PTR _Source);

   

public:
    Outliner();
    ~Outliner();
};

enum class COMPONENT_LIST
{
	TRANSFORM,
	COLLIDER2D,
	COLLIDER3D,
	ANIMATOR2D,
	ANIMATOR3D,
	LIGHT2D,
	LIGHT3D,
	CAMERA,
	STATEMACHINE,
	MESHRENDER,
	TILEMAP,
	PARTICLESYSTEM,
	SKYBOX,
	DECAL,
	LANDSCAPE

};

void SelectRObject(DWORD_PTR _Node);
void FillComponentComboVector(vector<string>& _vec);
void NewComponent(CGameObject* _obj, COMPONENT_TYPE _num);