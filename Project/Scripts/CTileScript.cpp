#include "pch.h"
#include "CTileScript.h"

#include "Engine/CAssetMgr.h"


CTileScript::CTileScript()
	:CScript(TILESCRIPT)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Normal State", &StateTimer[(int)TileState::Normal]);
	AddScriptParam(SCRIPT_PARAM::FLOAT, "On State", &StateTimer[(int)TileState::On]);
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Breaking State", &StateTimer[(int)TileState::Breaking]);
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Break State", &StateTimer[(int)TileState::Break]);
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Burn State", &StateTimer[(int)TileState::Burn]);
}

CTileScript::CTileScript(const CTileScript& _Origin)
	 : CScript(TILESCRIPT)
{
	for (int i = 0; i < (int)TileState::End; ++i)
	{
		StateTimer[i] = _Origin.StateTimer[i];
	}


	AddScriptParam(SCRIPT_PARAM::FLOAT, "Normal State", &StateTimer[(int)TileState::Normal]);
	AddScriptParam(SCRIPT_PARAM::FLOAT, "On State", &StateTimer[(int)TileState::On]);
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Breaking State", &StateTimer[(int)TileState::Breaking]);
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Break State", &StateTimer[(int)TileState::Break]);
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Burn State", &StateTimer[(int)TileState::Burn]);

	for (int i = 0; i < (int)TileChildType::End; ++i)
	{
		if (_Origin.TileChild[i] != nullptr)
			TileChild[i] = _Origin.TileChild[i]->Clone();

	}
}

CTileScript::~CTileScript()
{
}


void CTileScript::begin()
{
	TileMtrl = GetRenderComponent()->GetDynamicMaterial();

	SpawnChild();
	//
	TileMtrl->SetScalarParam(SCALAR_PARAM::INT_0, Camp);
}

void CTileScript::tick()
{
	// 상태 타이머 tick
	for (int i = 0; i < (int)TileState::End; ++i)
	{
		if (StateTimer[i] > 0.f)
		{
			StateTimer[i] -= DT;
		}

		if (StateTimer[i] <= 0.f)
		{
			StateTimer[i] = 0.f;

		}
	}

}

void CTileScript::SaveToFile(ofstream& _File)
{

}

void CTileScript::LoadFromFile(ifstream& _File)
{

}

bool CTileScript::CheckState(TileState _State)
{
	if(_State != TileState::Normal)
		return StateTimer[(int)_State] > 0.f;

	 for(int i = 0; i < (int)TileState::End; ++i)
	 {
		 if(StateTimer[i] > 0.f)
		 {
			 return false;
		 }
	 }

	 return true;
}


void CTileScript::SpawnChild()
{
	CGameObject* TempObject = nullptr;
	Ptr<CPrefab> TempPrefab = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\InTile.pref", L"prefab\\InTile.pref");

	// 타일 내부
	TempObject = TempPrefab->Instantiate();
	GamePlayStatic::SpawnGameObject(TempObject, 0);
	this->GetOwner()->AddChild(TempObject);

	TileChild[0] = TempObject;


	TempPrefab = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\TileBreak.pref", L"prefab\\TileBreak.pref");

	// 깨진 타일 이미지
	TempObject = TempPrefab->Instantiate();
	GamePlayStatic::SpawnGameObject(TempObject, 0);
	this->GetOwner()->AddChild(TempObject);

	TileChild[1] = TempObject;


	TempPrefab = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\TileShadow.pref", L"prefab\\TileShadow.pref");

	// 타일 그림자
	TempObject = TempPrefab->Instantiate();
	GamePlayStatic::SpawnGameObject(TempObject, 0);
	this->GetOwner()->AddChild(TempObject);

	TileChild[2] = TempObject;

	// 에니메이터
	TempObject = new CGameObject;
	TempObject->SetName(L"TILE Animator");
	TempObject->AddComponent(new CTransform);
	TempObject->AddComponent(new CAnimator2D);

	GamePlayStatic::SpawnGameObject(TempObject, 0);
	this->GetOwner()->AddChild(TempObject);


	TileChild[3] = TempObject;



}


void CTileScript::SetTilePosition(int row, int col)
{
	Transform()->SetRelativePos(Vec3(TileStartPointx + (Tilespacex + TileX) * col, TileStartPointy + (Tilespacey + TileY) * row, 500));
}

void CTileScript::SetTimer(TileState _State, float _Time)
{
	StateTimer[(int)_State] = _Time;
}

void CTileScript::AddTimer(TileState _State, float _Time)
{
	StateTimer[(int)_State] += _Time;

}

void CTileScript::ClearTimerAll()
{
	for(int i = 0; (int)TileState::End; ++i)
	{
		ClearTimer(TileState(i));
	}
}

void CTileScript::ClearTimer(TileState _State)
{
	StateTimer[(int)_State] = 0.f;
}
