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
	
	TileMtrl->SetScalarParam(SCALAR_PARAM::INT_0, Camp);
}

void CTileScript::tick()
{
	// ���� Ÿ�̸� tick
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
	//Field obj�� ��ȣ�ۿ�

	//Tile ���¿� ���� ��ȣ�ۿ�

	// ���� �����ΰ�??
	bool TileStatelist[(int)TileState::End] = { false };

	for(int i = 0; i < (int)TileState::End; ++i)
	{
		if(CheckState((TileState)i))
		{
			TileStatelist[i] = true;
		}
	}

	//���¿� ���� ó���� ��� �� ���ΰ�??
	//�迭�� ������ �迭�� ���������� ���鼭 switch case�� ��ȸ �ϸ鼭
	//�ش� ���°� �ִٸ� �ش� ������ ó���Ѵ�. ( ȿ��,  �̹��� ���� ��)

	// Breaking
	// ��ü�� �ö�� �� �ִ�. ������ �ö�ͼ� �̵����ڸ��� break
	// break tile


	// Break
	//break ���¶�� ��ü�� �ö� �� ������ ison�� üũ�ؼ� ó��
	

	//burn
	// brun ���¶�� �浹�� ��ü�� field obj�϶�, �������� �ֵ����Ѵ�.

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


void CTileScript::SpawnChild()
{
	bool isexist = false;
	CheckExist(isexist);
	if (isexist == true)
		return;
	
	CGameObject* TempObject = nullptr;
	Ptr<CPrefab> TempPrefab = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\InTile.pref", L"prefab\\InTile.pref");

	// Ÿ�� ����
	TempObject = TempPrefab->Instantiate();
	GamePlayStatic::SpawnGameObject(TempObject, 0);
	this->GetOwner()->AddChild(TempObject);

	TileChild[0] = TempObject;


	TempPrefab = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\TileBreak.pref", L"prefab\\TileBreak.pref");

	// ���� Ÿ�� �̹���
	TempObject = TempPrefab->Instantiate();
	GamePlayStatic::SpawnGameObject(TempObject, 0);
	this->GetOwner()->AddChild(TempObject);

	TileChild[1] = TempObject;


	TempPrefab = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\TileShadow.pref", L"prefab\\TileShadow.pref");

	// Ÿ�� �׸���
	TempObject = TempPrefab->Instantiate();
	GamePlayStatic::SpawnGameObject(TempObject, 0);
	this->GetOwner()->AddChild(TempObject);

	TileChild[2] = TempObject;

	// ���ϸ�����
	TempObject = new CGameObject;
	TempObject->SetName(L"TileAnimator");
	TempObject->AddComponent(new CTransform);
	TempObject->AddComponent(new CAnimator2D);

	GamePlayStatic::SpawnGameObject(TempObject, 0);
	this->GetOwner()->AddChild(TempObject);


	TileChild[3] = TempObject;



}

void CTileScript::CheckExist(bool& check)
{
	for (int i = 0; i < (int)TileChildType::End; ++i)
	{
		if (TileChild[i] != nullptr)
		{
			check = true;
			break;
		}
	}

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
