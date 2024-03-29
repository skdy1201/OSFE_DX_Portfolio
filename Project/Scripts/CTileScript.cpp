#include "pch.h"
#include "CTileScript.h"

#include "Engine/CAssetMgr.h"


CTileScript::CTileScript()
	:CScript(TILESCRIPT)
{
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

	AddScriptParam(SCRIPT_PARAM::FLOAT, "Breaking State", &StateTimer[(int)TileState::Breaking]);
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Break State", &StateTimer[(int)TileState::Break]);
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Burn State", &StateTimer[(int)TileState::Burn]);

}

CTileScript::~CTileScript()
{
}


void CTileScript::begin()
{
	TileMtrl = GetRenderComponent()->GetDynamicMaterial();
	
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

void CTileScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	//Field obj와 상호작용

	//Tile 상태에 대한 상호작용

	// 무슨 상태인가??
	bool TileStatelist[(int)TileState::End] = { false };

	for(int i = 0; i < (int)TileState::End; ++i)
	{
		if(CheckState((TileState)i))
		{
			TileStatelist[i] = true;
		}
	}

	//상태에 대한 처리를 어떻게 할 것인가??
	//배열이 있으니 배열의 마지막까지 돌면서 switch case로 순회 하면서
	//해당 상태가 있다면 해당 동작을 처리한다. ( 효과,  이미지 변경 등)

	// Breaking
	// 객체가 올라올 수 있다. 하지만 올라와서 이동하자마자 break
	// break tile


	// Break
	//break 상태라면 객체가 올라갈 수 없으니 ison을 체크해서 처리
	

	//burn
	// brun 상태라면 충돌한 객체가 field obj일때, 데미지를 주도록한다.

}

void CTileScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	
}

void CTileScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	
}

void CTileScript::SaveToFile(ofstream& _File)
{

}

void CTileScript::LoadFromFile(ifstream& _File)
{

}

bool CTileScript::CheckState(TileState _State)
{

	return StateTimer[(int)_State] > 0.f;

}

void CTileScript::SetTilePosition(int row, int col)
{
	Vec3 Ttransform = Vec3(TileStartPointx + (Tilespacex + TileX) * col, TileStartPointy + (Tilespacey + TileY) * row, 500);
	Transform()->SetRelativePos(Ttransform);
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
