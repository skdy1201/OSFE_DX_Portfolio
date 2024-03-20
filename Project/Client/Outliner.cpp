#include "pch.h"
#include "Outliner.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>
#include <Engine/CKeyMgr.h>

#include "CImGuiMgr.h"
#include "Inspector.h"
#include "TreeUI.h"

#include <Engine/CTaskMgr.h>
#include <Engine/CTransform.h>

#include <Engine/components.h>
#include  <Scripts/CScriptMgr.h>
#include <Engine/CScript.h>

#include <Engine/CTaskMgr.h>

Outliner::Outliner()
	: UI("Outliner", "##Outliner")
{
	m_Tree = new TreeUI("OutlinerTree");
	m_Tree->ShowRootNode(false);
	m_Tree->UseDragDrop(true);

	AddChildUI(m_Tree);

	// Ʈ���� Ŭ�� �̺�Ʈ ���
	m_Tree->AddSelectDelegate(this, (Delegate_1)&Outliner::SelectObject);
	m_Tree->AddSelectRCallback(this, (CALL_BACK_1)&::SelectRObject);
	m_Tree->AddDragDropDelegate(this, (Delegate_2)&Outliner::DragDropObject);
	

	// Ʈ�� ������ ���� ������ ��ü��� ����
	ResetCurrentLevel();
}

Outliner::~Outliner()
{
}

void Outliner::render_update()
{
	if (CTaskMgr::GetInst()->GetObjectEvent())
	{
		ResetCurrentLevel();
	}

	if (KEY_TAP(KEY::DEL))
	{
		TreeNode* pNode = m_Tree->GetSelectedNode();
		if (nullptr != pNode)
		{
			CGameObject* pSelectObj = (CGameObject*)pNode->GetData();
			GamePlayStatic::DestroyGameObject(pSelectObj);
		}
	}
}

void Outliner::ResetCurrentLevel()
{
	// Ʈ�� ������ ����
	m_Tree->ClearNode();

	// ���� ������ �����´�.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	if (nullptr == pCurLevel)
		return;

	// Ʈ���� ��Ʈ �߰�
	TreeNode* pRootNode = m_Tree->AddTreeNode(nullptr, "DummyRoot", 0);

	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		CLayer* pLayer = pCurLevel->GetLayer(i);
		const vector<CGameObject*>& vecParent = pLayer->GetParentObjects();

		for (size_t i = 0; i < vecParent.size(); ++i)
		{
			AddObjectToTree(pRootNode, vecParent[i]);
		}
	}
}

void Outliner::AddObjectToTree(TreeNode* _Node, CGameObject* _Object)
{
	TreeNode* pNode = m_Tree->AddTreeNode(_Node, string(_Object->GetName().begin(), _Object->GetName().end()), (DWORD_PTR)_Object);

	const vector<CGameObject*>& vecChild = _Object->GetChild();

	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		AddObjectToTree(pNode, vecChild[i]);
	}
}

void Outliner::SelectObject(DWORD_PTR _Node)
{
	TreeNode* pNode = (TreeNode*)_Node;
	CGameObject* pObject = (CGameObject*)pNode->GetData();

	if (nullptr == pObject)
		return;

	Inspector* pInspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
	pInspector->SetTargetObject(pObject);	
}




void Outliner::DragDropObject(DWORD_PTR _Dest, DWORD_PTR _Source)
{
	TreeNode* pDestNode = (TreeNode*)_Dest;
	TreeNode* pSourceNode = (TreeNode*)_Source;

	CGameObject* pDestObj = nullptr;
	if(nullptr != pDestNode)
		pDestObj = (CGameObject*)pDestNode->GetData();

	CGameObject* pSourceObj = (CGameObject*)pSourceNode->GetData();

	// �θ� ������Ʈ�� �ڽ��� �ڽĿ�����Ʈ�� �ڽ����� ������ ���� ����
	if (pDestObj != nullptr && pDestObj->IsAncestor(pSourceObj))
		return;

	if (nullptr == pDestNode)
	{
		int LayerIdx = pSourceObj->DisconnectWithParent();

		// ���� �θ� ������
		if (LayerIdx == -1)
			return;

		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		pCurLevel->AddObject(pSourceObj, LayerIdx, false);
	}
	else
	{		
		pDestObj->AddChild(pSourceObj);
	}

	ResetCurrentLevel();
}

void FillComponentComboVector(vector<string>& _vec)
{
	_vec.push_back("TRANSFORM");
	_vec.push_back("COLLIDER2D");
	_vec.push_back("COLLIDER3D");
	_vec.push_back("ANIMATOR2D");
	_vec.push_back("ANIMATOR3D");
	_vec.push_back("LIGHT2D");
	_vec.push_back("LIGHT3D");
	_vec.push_back("CAMERA");
	_vec.push_back("STATEMACHINE");
	_vec.push_back("MESHRENDER");
	_vec.push_back("TILEMAP");
	_vec.push_back("PARTICLESYSTEM");
	_vec.push_back("SKYBOX");
	_vec.push_back("DECAL");
	_vec.push_back("LANDSCAPE");
}

void NewComponent(CGameObject* _obj, COMPONENT_TYPE _num)
{
	CComponent* temp = nullptr;

	switch (_num)
	{
	case COMPONENT_TYPE::TRANSFORM:
		_obj->AddComponent(new CTransform);
		break;
	case COMPONENT_TYPE::COLLIDER2D:
		_obj->AddComponent(new CCollider2D);
		break;
	case COMPONENT_TYPE::COLLIDER3D:
		break;
	case COMPONENT_TYPE::ANIMATOR2D:
		_obj->AddComponent(new CAnimator2D);
		break;
	case COMPONENT_TYPE::ANIMATOR3D:
		break;
	case COMPONENT_TYPE::LIGHT2D:
		_obj->AddComponent(new CLight2D);
		break;
	case COMPONENT_TYPE::LIGHT3D:
		break;
	case COMPONENT_TYPE::CAMERA:
		_obj->AddComponent(new CCamera);
		break;
	case COMPONENT_TYPE::STATEMACHINE:
		_obj->AddComponent(new CStateMachine);
		break;
	case COMPONENT_TYPE::MESHRENDER:
		_obj->AddComponent(new CMeshRender);
		break;
	case COMPONENT_TYPE::TILEMAP:
		_obj->AddComponent(new CTileMap);
		break;
	case COMPONENT_TYPE::PARTICLESYSTEM:
		_obj->AddComponent(new CParticleSystem);
		break;
	case COMPONENT_TYPE::SKYBOX:
		break;
	case COMPONENT_TYPE::DECAL:
		break;
	case COMPONENT_TYPE::LANDSCAPE:
		break;
	}
}


void SelectRObject(DWORD_PTR _Node)
{

	TreeNode* pNode = (TreeNode*)_Node;
	CGameObject* pObject = (CGameObject*)pNode->GetData();

	if (pObject == nullptr || pNode == nullptr)
	{
		pNode->SetSelectedRCancel();
		ImGui::CloseCurrentPopup();
		return;
	}

		

	if(ImGui::BeginPopupContextItem("RightClickOutlinerMenu"))
	{
		if(pObject->IsDead() == true)
		{
			ImGui::EndPopup();
			return;
		}

		static char value[128] = "";
		char CurObject[128] = " ";

		string temp = ToString(pObject->GetName()).c_str();
		strcpy(CurObject, temp.c_str());


		ImGui::Text("Current Input: %s", CurObject);

		static int menuPage = 0; // ���� ������ �޴� �������� �����ϴ� ���� ����

		// �������� ���� �ٸ� ������ ������
		if (menuPage == 0)
		{
			// ù ��° �������� �޴� �׸�
			ImGui::InputText("##Prefab Key", value, IM_ARRAYSIZE(value));

			ImGui::Text("Save Key = %s", value);


			if (ImGui::Button("SAVE", ImVec2{ 60.f, 30.f }))
			{
				//set game obj
				CGameObject* pCloneObj = pObject->Clone();

				CPrefab* pTempPrefab = new CPrefab(pCloneObj, false);

				wstring ContentPath = L"prefab\\";
				wstring changechar = ToWString(value);

				ContentPath += changechar;
				ContentPath += L".pref";

				pTempPrefab->Save(ContentPath);

				delete pTempPrefab;

				ImGui::CloseCurrentPopup();
			}

			ImGui::SameLine();

			if(ImGui::Button("Delete", ImVec2{ 60.f, 30.f }))
			{
				tTask temp = {};

				temp.Type = TASK_TYPE::DELETE_OBJECT;
				temp.Param_1 = (DWORD_PTR)pObject;

				CTaskMgr::GetInst()->AddTask(temp);

				auto ui = CImGuiMgr::GetInst()->FindUI("##Outliner");
				auto outliner = dynamic_cast<Outliner*>(ui);

				outliner->GetTree()->SetSelectedRNode(nullptr);

				outliner->ResetCurrentLevel();



			}
			

			if (ImGui::Button("Next Page", ImVec2(100.f, 30.f)))
			{
				menuPage = 1;
			}


		}
		else if (menuPage == 1)
		{
			vector<string> ComponentList;

			FillComponentComboVector(ComponentList);

			// ImGui::Combo�� �ʿ��� const char* �迭 ����
			vector<const char*> Items;
			for (const auto& Item : ComponentList) 
			{
				Items.push_back(Item.c_str());
			}

			ImGui::Text("AddComponent");
			ImGui::SameLine();

			// ���� ���õ� ������Ʈ �ε���
			static int Component_current = 0;

			// ImGui::Combo�� �׸��ϴ�.
			// Items.data()�� const char*�� �迭�� �����ϸ�,
			// Items.size()�� �׸��� ������ �����մϴ�.
			ImGui::Combo("##SelectComponent", &Component_current, Items.data(), static_cast<int>(Items.size()));

			ImGui::SameLine();

			if (ImGui::Button("Add to Object", ImVec2{ 120, 30 }))
			{

				COMPONENT_TYPE temp = (COMPONENT_TYPE)Component_current;

				NewComponent(pObject, temp);
			}

			if (ImGui::Button("Prev Page", ImVec2(100.f, 30.f)))
			{
				menuPage = 0;
			}

			ImGui::SameLine();

			if (ImGui::Button("Next Page", ImVec2(100.f, 30.f)))
			{
				menuPage = 2;
			}
		}
		else if (menuPage == 2)
		{
			ImGui::Separator();

			ImGui::NewLine();

			ImGui::Text("ScriptList", ImVec2{ 50, 40 });

			ImGui::NewLine();

			// ������ ��� (���� ���ø����̼ǿ����� ���� �������� �� ����)
			vector<wstring> ScriptList;
			CScriptMgr::GetScriptInfo(ScriptList);


			// �˻�� ������ ����
			static char searchQuery[256] = "";

			ImGui::Text("Search");
			ImGui::SameLine();
			ImGui::InputText("##Search", searchQuery, IM_ARRAYSIZE(searchQuery));  // �˻��� �Է� �ʵ�

			for (size_t i = 0; i < ScriptList.size(); ++i)
			{
				// ToString �Լ��� ����Ͽ� wstring�� string���� ��ȯ
				string scriptName = ToString(ScriptList[i]);

				// �˻�� ����ְų�, ��ũ��Ʈ �̸��� �˻�� �����ϴ� ��쿡�� �׸� ǥ��
				if (searchQuery[0] == '\0' || scriptName.find(searchQuery) != std::string::npos)
				{
					if (ImGui::MenuItem(scriptName.c_str()))
					{
						auto script = CScriptMgr::GetScript(ToWString(scriptName));
						pObject->AddComponent(script);

					}
				}
			}

			if (ImGui::Button("Prev Page", ImVec2(100.f, 30.f)))
			{
				menuPage = 1;
			}
		}

		ImGui::EndPopup();
	}




	ImGui::OpenPopup("RightClickOutlinerMenu");
	{
	}

	
}






