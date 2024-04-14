#include "pch.h"
#include "CCreateTempLevel.h"


#include <Engine/CCollisionMgr.h>

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>
#include <Engine/components.h>

#include <Scripts/CPlayerScript.h>
#include <Scripts/CBackgroundScript.h>

#include <Engine/CMesh.h>
#include <Engine/CGraphicsShader.h>
#include <Engine/CTexture.h>
#include <Engine/CSetColorShader.h>

#include "CLevelSaveLoad.h"
#include <Scripts/CMissileScript.h>
#include <Scripts/CMonsterScript.h>

#include <Engine/CAssetMgr.h>
#include <Engine/CPrefab.h>
#include <Engine/CFSM.h>

#include "CCameraMoveScript.h"
#include "CIdleState.h"
#include "CTraceState.h"

#include <Scripts/CTileScript.h>

#include "../Scripts/define.h"

#include <Engine/CAnimator2D.h>


void CCreateTempLevel::Init()
{
	// Missile Prefab 생성
	/*CGameObject* pObj = nullptr;

	pObj = new CGameObject;
	pObj->SetName(L"Missile");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CMissileScript);

	pObj->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 1.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	Ptr<CPrefab> pMissilePrefab = new CPrefab(pObj, false);
	CAssetMgr::GetInst()->AddAsset<CPrefab>(L"MissilePrefab", pMissilePrefab.Get());
	

	pMissilePrefab->Save(L"prefab\\missile.pref");*/
	

	// 임시 FSM 객체 에셋 하나 생성하기
	Ptr<CFSM>	pFSM = new CFSM(true);

	pFSM->AddState(L"IdleState", new CIdleState);
	pFSM->AddState(L"TraceState", new CTraceState);

	CAssetMgr::GetInst()->AddAsset<CFSM>(L"NormalMonsterFSM", pFSM.Get());
}

void CCreateTempLevel::CreateTempLevel()
{		
	/*Ptr<CMaterial> pBackgroudMtrl = CAssetMgr::GetInst()->FindAsset<CMaterial>(L"BackgroundMtrl");
	Ptr<CMaterial> pStd2DMtrl = CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl");

	pBackgroudMtrl->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Background.jpg", L"texture\\Background.jpg"));
	pStd2DMtrl->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Fighter.bmp", L"texture\\Fighter.bmp"));*/

	/*CLevel* pLevel = CLevelSaveLoad::LoadLevel(L"level\\temp.lv");
	CLevelMgr::GetInst()->ChangeLevel(pLevel, LEVEL_STATE::STOP);
	return;*/


	CLevel* pTempLevel = new CLevel;

	pTempLevel->GetLayer(0)->SetName(L"Default");
	pTempLevel->GetLayer(1)->SetName(L"Field");
	pTempLevel->GetLayer(2)->SetName(L"Tile");
	pTempLevel->GetLayer(3)->SetName(L"Player");
	pTempLevel->GetLayer(4)->SetName(L"Monster");
	pTempLevel->GetLayer(5)->SetName(L"Light");
	pTempLevel->GetLayer(31)->SetName(L"UI");

	// ComputeShader 테스트
	// 사용할 텍스쳐 생성
	Ptr<CTexture> pTestTex = CAssetMgr::GetInst()->CreateTexture(L"TestTex"
		, 1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM
		, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);

	Ptr<CSetColorShader> pCS = (CSetColorShader*)CAssetMgr::GetInst()->FindAsset<CComputeShader>(L"SetColorShader").Get();
	pCS->SetColor(Vec3(1.f, 0.f, 0.f));
	pCS->SetTargetTexture(pTestTex);
	pCS->Execute();

	tPixel* pPixel = pTestTex->GetPixels();
	tPixel pixel = pPixel[pTestTex->GetWidth() * 1 + 5];

	// Main Camera Object 생성
	CGameObject* pCamObj = new CGameObject;
	pCamObj->SetName(L"MainCamera");
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);

	pCamObj->Transform()->SetRelativePos(Vec3(0.5f, 0.f, 0.f));
	pCamObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));

	pCamObj->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	pCamObj->Camera()->SetCameraPriority(0);
	pCamObj->Camera()->LayerCheckAll();
	pCamObj->Camera()->LayerCheck(31, false);

	pTempLevel->AddObject(pCamObj, LayerDefault);

	// UI 카메라 생성
	pCamObj = new CGameObject;
	pCamObj->SetName(L"UICamera");
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);
	pCamObj->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);

	pCamObj->Transform()->SetRelativePos(Vec3(0.5f, 0.f, 0.f));
	pCamObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));

	pCamObj->Camera()->SetCameraPriority(1);
	pCamObj->Camera()->LayerCheck(31, true);

	pTempLevel->AddObject(pCamObj, LayerDefault);

	// 전역 광원 추가
	CGameObject* pLight = new CGameObject;
	pLight->SetName(L"DirectionalLight");
	pLight->AddComponent(new CTransform);
	pLight->AddComponent(new CLight2D);

	pLight->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLight->Light2D()->SetAmbient(Vec3(0.8f, 0.8f, 0.8f));
	pTempLevel->AddObject(pLight, LayerLight);


	CGameObject* pObj = nullptr;

	// Backgruond Object 생성
	//pObj = new CGameObject;
	//pObj->SetName(L"Background");

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CBackgroundScript);

	//pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, BackGroundZ));
	//pObj->Transform()->SetRelativeScale(Vec3(1600.f, 800.f, 1.f));

	//pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"BackgroundMtrl"));

	//Ptr<CTexture> pTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Background.jpg", L"texture\\Background.jpg");
	//pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, pTex);

	//pTempLevel->AddObject(pObj, LayerBackGround, false);

	// Player Object 생성
	/*pObj = new CGameObject;
	pObj->SetName(L"Player");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CPlayerScript);
	pObj->AddComponent(new CMissileScript);

	pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 500.f));
	pObj->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 1.f));

	pObj->Collider2D()->SetAbsolute(true);
	pObj->Collider2D()->SetOffsetScale(Vec2(100.f, 100.f));
	pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	pTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Character.png", L"texture\\Character.png");

	pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Character.png", L"texture\\Character.png"));

	pTempLevel->AddObject(pObj, L"Player", false);*/


	// Monster Object 생성
	/*pObj = new CGameObject;
	pObj->SetName(L"Monster");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CStateMachine);
	pObj->AddComponent(new CMonsterScript);

	pObj->Transform()->SetRelativePos(Vec3(500.f, 0.f, 500.f));
	pObj->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 1.f));

	pObj->Collider2D()->SetAbsolute(true);
	pObj->Collider2D()->SetOffsetScale(Vec2(120.f, 120.f));
	pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));
	pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Character.png", L"texture\\Character.png"));

	pObj->StateMachine()->SetFSM(CAssetMgr::GetInst()->FindAsset<CFSM>(L"NormalMonsterFSM"));

	pTempLevel->AddObject(pObj, L"Monster", false);*/


	Ptr<CPrefab> temp = CAssetMgr::GetInst()->Load<CPrefab>(FieldPrefabKey, FieldPrefabKey);
	pObj = temp->Instantiate();
	pTempLevel->AddObject(pObj, LayerField, true);

	 temp = CAssetMgr::GetInst()->Load<CPrefab>(PrefabManaUI, PrefabManaUI);
	pObj = temp->Instantiate();
	pTempLevel->AddObject(pObj, LayerUI, true);

	 temp = CAssetMgr::GetInst()->Load<CPrefab>(PrefabBackGround, PrefabBackGround);
	pObj = temp->Instantiate();
	pTempLevel->AddObject(pObj, LayerBackGround, true);

	temp = CAssetMgr::GetInst()->Load<CPrefab>(PrefabDeckCoverUI, PrefabDeckCoverUI);
	pObj = temp->Instantiate();
	pTempLevel->AddObject(pObj, LayerUI, true);

	temp = CAssetMgr::GetInst()->Load<CPrefab>(PrefabHandSlotQ, PrefabHandSlotQ);
	pObj = temp->Instantiate();
	pTempLevel->AddObject(pObj, LayerUI, true);

	temp = CAssetMgr::GetInst()->Load<CPrefab>(PrefabHandSlotW, PrefabHandSlotW);
	pObj = temp->Instantiate();
	pTempLevel->AddObject(pObj, LayerUI, true);

	temp = CAssetMgr::GetInst()->Load<CPrefab>(PrefabTopInfo, PrefabTopInfo);
	pObj = temp->Instantiate();
	pTempLevel->AddObject(pObj, LayerUI, true);

	// 충돌 설정
	CCollisionMgr::GetInst()->LayerCheck(LayerPlayerAttack, LayerMonster);
	CCollisionMgr::GetInst()->LayerCheck(LayerMonsterAttack, LayerPlayer);
	CCollisionMgr::GetInst()->LayerCheck(LayerMonsterAttackonTile, LayerTile);
	CCollisionMgr::GetInst()->LayerCheck(LayerMonsterAttackonTile, LayerPlayer);

	CCollisionMgr::GetInst()->LayerCheck(4, 4);

	CLevelMgr::GetInst()->ChangeLevel(pTempLevel, LEVEL_STATE::STOP);

	//CLevelSaveLoad::SaveLevel(pTempLevel, L"level\\temp.lv");	
}