#include "pch.h"
#include "CSubAnimator2DUI.h"
#include "Animator2DUI.h"

#include  <Engine/CTimeMgr.h>

#include <Engine/CGameObject.h>
#include <Engine/CAssetMgr.h>
#include <Engine/CMaterial.h>
#include <Engine/CGraphicsShader.h>
#include <Engine/CTexture.h>

#include<Engine\CAnimator2D.h>
#include <Engine\CAnim.h>




CSubAnimator2DUI::CSubAnimator2DUI(Animator2DUI* Parent)
	: UI("Animator2DSub", "##Animator2DSub")
	, Super(Parent)
	, OneFrmSize(0.f, 0.f)
	, Fullfrmidx{ 0.f, 0.f }
	, LeftTop{ 0.f, 0.f }
	, Offset{ 0.f, 0.f }
	, Background{ 0.f, 0.f }
	, frmcount(0)
	, Duration(0.f)
	, OneAnim(nullptr)
	, AtlasCol(0)
	, AtlasRow(0)
	, IsSetIdx(false)
	, Padding(0, 0)
	, CurFrmNum(-1)
	, ShowAnimKey{ }
	, PreviewStop(true)
	, now(0)
	,PrintAtlasSize{0, 0}
{
	SetSize(ImVec2(800.f, 720.f));
	m_TargetObject = Super->GetTargetObj();
}

CSubAnimator2DUI::~CSubAnimator2DUI()
{
}

void CSubAnimator2DUI::render_update()
{
	//이미지를 딱 맞추고 싶다면 아틀라스 이미지 로딩, grid 부분의 xy를 조정

	TargetAnimator2D = Super->GetTargetObj()->Animator2D();

	//기본 세팅
	bool check = this->IsActivate();
	ImGui::SetWindowSize(this->GetSize());

	
	if(ImGui::Begin("Animator2DSub", &check))

	if (ImGui::BeginTabBar("AnimatorTab"))
	{
		if (ImGui::BeginTabItem("Create"))
		{


			//아틀라스 이미지 로딩
			if (m_AtlasTex != nullptr)
			{
				static bool use_text_color_for_tint = false;
				ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
				ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
				ImVec4 tint_col = use_text_color_for_tint ? ImGui::GetStyleColorVec4(ImGuiCol_Text) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // No tint
				ImVec4 border_col = ImGui::GetStyleColorVec4(ImGuiCol_Border);

				// 아틀라스 위치 얻어오기
				ImVec2 Atlaspos = ImGui::GetCursorScreenPos();
				AtlasPosition = Atlaspos;
				ImGui::Image(m_AtlasTex->GetSRV().Get(), ImVec2(1000, 500), uv_min, uv_max, tint_col, border_col);

				RealAtlasPixel.x = m_AtlasTex.Get()->GetWidth();
				RealAtlasPixel.y = m_AtlasTex.Get()->GetHeight();

				PrintAtlasSize = { 1000, 500 };
			}
			else
			{

				ImGui::Dummy(ImVec2(500, 500));
			}

			if (AtlasCol != 0 && AtlasRow != 0)
				CheckIndex(AtlasCol, AtlasRow);

			//마우스 짜기
			ImGuiIO& io = ImGui::GetIO();
			ImVec2 mousePos = io.MousePos; // 마우스 커서의 절대 위치
			ImVec2 mousePosOnImage = ImVec2(mousePos.x - AtlasPosition.x, mousePos.y - AtlasPosition.y); // 이미지 위에서의 상대 위치

			// 마우스 커서가 이미지 위에 있는지 확인
			if (m_AtlasTex != nullptr &&
				mousePosOnImage.x >= 0 && mousePosOnImage.x < 1000 &&
				mousePosOnImage.y >= 0 && mousePosOnImage.y < 500)
			{
				// mousePosOnImage.x, mousePosOnImage.y는 마우스 커서의 이미지 위에서의 상대적 위치
				float scaleX = RealAtlasPixel.x / 1000;
				float scaleY = RealAtlasPixel.y / 500;

				// 실제 이미지 픽셀 위치 계산
				float realX = mousePosOnImage.x * scaleX;
				float realY = mousePosOnImage.y * scaleY;

				ImGui::Text("Mouse Pos on Image: (%.1f, %.1f)", realX, realY);

				if (ImGui::IsMouseClicked(0))
				{
					ImVec2 frmidxcol = CheckIndex(realX, realY);
					Fullfrmidx.x = frmidxcol.x;
					Fullfrmidx.y = frmidxcol.y;
				}

			}


			// 그리드 그리기
			if (IsSetIdx)
			{
				int ColRow[2] = {AtlasCol, AtlasRow};
				DrawGrid(AtlasPosition, PrintAtlasSize, Padding, ColRow);
			}

			LoadAtlasButton("Load Atlas", ImVec2(40, 40));
			
			// 나눌 행렬, 프레임 카운트 설정
			ImGui::SameLine();
			ImGui::SetNextItemWidth(75);
			ImGui::InputInt("Col", &AtlasCol);

			ImGui::SameLine();
			ImGui::SetNextItemWidth(75);
			ImGui::InputInt("Row", &AtlasRow);

			ImGui::Text("MakeFrmNum: %d", frmcount);

			//현재 아틀라스에서 한 프레임 구조 짜기
			FloatAnimStruct();

			// 현재 아틀라스에서 프레임 추가하기
			AddFrmButton("AddFrm", ImVec2{ 60.f , 30.f });
			

			ImGui::SameLine();

			// 프레임 벡터 초기화
			if (ImGui::Button("ClearAnim", ImVec2{ 60.f , 30.f }))
			{
				AnimClear();
			}


			ImGui::EndTabItem();
		}
		//save 부분 구현
		if (ImGui::BeginTabItem("Save"))
		{
			// 프레임 이미지 로딩
			if (tm_vecFrm.size() != 0)
			{
				int ShowCurFrmNum = CurFrmNum;

				// 환산을 위한 아틀라스의 실제 크기
				float atlasWidth = m_AtlasTex->GetWidth();
				float atlasHeight = m_AtlasTex->GetHeight();

				// 오프셋받아오기 -> 이것도 결국 환산된 비율이다.
				ImVec2 ShowFrmOffset = {
					tm_vecFrm[ShowCurFrmNum].vOffset.x,
					tm_vecFrm[ShowCurFrmNum].vOffset.y
				};

				// 백그라운드 + offset
				ImVec2 ShowBackGroundPix = {
					tm_vecFrm[ShowCurFrmNum].vBackground.x * atlasWidth,
					tm_vecFrm[ShowCurFrmNum].vBackground.y * atlasHeight
				};


				// 프레임의 좌상단 위치를 실제 픽셀 위치로 환산
				ImVec2 ShowLeftTopPix = {
					(tm_vecFrm[ShowCurFrmNum].vLeftTop.x) * atlasWidth,
					(tm_vecFrm[ShowCurFrmNum].vLeftTop.y) * atlasHeight
				};

				// 프레임의 크기를 실제 픽셀 크기로 환산
				ImVec2 ShowFrmCutsizePix = {
					tm_vecFrm[CurFrmNum].vSlice.x * atlasWidth,
					tm_vecFrm[CurFrmNum].vSlice.y * atlasHeight
				};

				// UV 좌표 계산
				ImVec2 uv_offset = ImVec2(ShowFrmOffset.x, ShowFrmOffset.y);

				ImVec2 uv_min = ImVec2(ShowLeftTopPix.x / atlasWidth, ShowLeftTopPix.y / atlasHeight);
				ImVec2 uv_max = ImVec2((ShowLeftTopPix.x + ShowFrmCutsizePix.x) / atlasWidth,
					(ShowLeftTopPix.y + ShowFrmCutsizePix.y) / atlasHeight);


				// UV 좌표에 오프셋 적용
				ImVec2 uv_min_adjusted = ImVec2(uv_min.x + uv_offset.x, uv_min.y + uv_offset.y);
				ImVec2 uv_max_adjusted = ImVec2(uv_max.x + uv_offset.x, uv_max.y + uv_offset.y);

				static bool use_text_color_for_tint = false;


				ImVec4 tint_col = use_text_color_for_tint ? ImGui::GetStyleColorVec4(ImGuiCol_Text) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // No tint
				ImVec4 border_col = ImGui::GetStyleColorVec4(ImGuiCol_Border);



				// ImGui::Image 호출
				ImGui::Image(m_AtlasTex->GetSRV().Get(), ShowBackGroundPix, uv_min_adjusted, uv_max_adjusted, tint_col, border_col);

				//frm 구조체 채우기
				FloatFrmStruct();
			}

			if (ImGui::Button("Fill Anim", ImVec2{ 100.f , 30.f }))
			{
				OneAnim = new CAnim;
				OneAnim->SetFrmvector(tm_vecFrm);
				OneAnim->SetName(Animation_Key);

			}

			if (ImGui::Button("Create Animation", ImVec2{ 100.f , 30.f }))
			{
				m_TargetObject = Super->GetTargetObj();

				OneAnim->SetAnimator(m_TargetObject->Animator2D());
				OneAnim->SetAtlas(m_AtlasTex);

				if (OneAnim != nullptr && m_TargetObject != nullptr)
				{
					m_TargetObject->Animator2D()->Create(Animation_Key, OneAnim);
				}
			}

			// preview 재생
			if(OneAnim != nullptr)
			{
				if(PreviewStop)
				{
					now = 0;
				
				}
				else
				{
					PlayPreview();
				}

				// 환산을 위한 아틀라스의 실제 크기
				float atlasWidth = m_AtlasTex->GetWidth();
				float atlasHeight = m_AtlasTex->GetHeight();

				// 오프셋받아오기 -> 이것도 결국 환산된 비율이다.
				ImVec2 ShowFrmOffset = {
					tm_vecFrm[now].vOffset.x,
					tm_vecFrm[now].vOffset.y
				};

				// 백그라운드 + offset
				ImVec2 ShowBackGroundPix = {
					tm_vecFrm[now].vBackground.x * atlasWidth,
					tm_vecFrm[now].vBackground.y * atlasHeight
				};


				// 프레임의 좌상단 위치를 실제 픽셀 위치로 환산
				ImVec2 ShowLeftTopPix = {
					(tm_vecFrm[now].vLeftTop.x) * atlasWidth,
					(tm_vecFrm[now].vLeftTop.y) * atlasHeight
				};

				// 프레임의 크기를 실제 픽셀 크기로 환산
				ImVec2 ShowFrmCutsizePix = {
					tm_vecFrm[now].vSlice.x * atlasWidth,
					tm_vecFrm[now].vSlice.y * atlasHeight
				};

				// UV 좌표 계산
				ImVec2 uv_offset = ImVec2(ShowFrmOffset.x, ShowFrmOffset.y);

				ImVec2 uv_min = ImVec2(ShowLeftTopPix.x / atlasWidth, ShowLeftTopPix.y / atlasHeight);
				ImVec2 uv_max = ImVec2((ShowLeftTopPix.x + ShowFrmCutsizePix.x) / atlasWidth,
					(ShowLeftTopPix.y + ShowFrmCutsizePix.y) / atlasHeight);


				// UV 좌표에 오프셋 적용
				ImVec2 uv_min_adjusted = ImVec2(uv_min.x + uv_offset.x, uv_min.y + uv_offset.y);
				ImVec2 uv_max_adjusted = ImVec2(uv_max.x + uv_offset.x, uv_max.y + uv_offset.y);

				static bool use_text_color_for_tint = false;


				ImVec4 tint_col = use_text_color_for_tint ? ImGui::GetStyleColorVec4(ImGuiCol_Text) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // No tint
				ImVec4 border_col = ImGui::GetStyleColorVec4(ImGuiCol_Border);



				// ImGui::Image 호출
				ImGui::Image(m_AtlasTex->GetSRV().Get(), ImVec2(400.f, 400.f*ShowBackGroundPix.y / ShowBackGroundPix.x), uv_min_adjusted, uv_max_adjusted, tint_col, border_col);
			}

			if (ImGui::Button("Play Preview", ImVec2{ 100.f , 30.f }))
			{
				PreviewStop = false;
			}

			if(ImGui::Button("SaveAnim", ImVec2(100.f, 30.f)))
			{
				if( OneAnim != nullptr)
				{
					SaveNewAnim();
				}
			}

			ImGui::SameLine();
			if(ImGui::Button("LoadAnim", ImVec2(100.f, 30.f)))
			{
				LoadAnim();
			}

			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}

		ImGui::End();
	
	//종료 조건
	if (!check)
	{
		this->Deactivate();
	}
	
}

wstring CSubAnimator2DUI::LoadFile()
{
	OPENFILENAME ofn;       // 공통 대화 상자 구조체
	wchar_t szFile[260];       // 파일 이름 버퍼

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL; // 현재 윈도우의 핸들
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"All Files\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		return (wstring)szFile;
	}
}

wstring CSubAnimator2DUI::MakePath(wstring FullPath)
{
	return FullPath.substr(FullPath.find(L"content") + 7);
}

wstring CSubAnimator2DUI::MakeKey(wstring FullPath)
{
	int pathslash = 0;
	int startidx = 0;

	for (int i = FullPath.size(); i > 0; --i)
	{

		if (FullPath[i] == '\\')
			++pathslash;

		if (pathslash == 1)
		{
			startidx = i + 1;
			break;
		}
	}

	return FullPath.substr(startidx);
}

ImVec2 CSubAnimator2DUI::CheckIndex(float col, float row)
{
	ImVec2 residx = { 0, 0 };

	int onecol = (int)RealAtlasPixel.x / AtlasCol;
	int onerow = (int)RealAtlasPixel.y / AtlasRow;

	OneFrmSize.x = (float)onecol;
	OneFrmSize.y = (float)onerow;

	for (int i = 0; i < AtlasCol; ++i) {
		// 컬럼 인덱스 검사
		if (onecol * i <= col && onecol * (i + 1) > col) {
			residx.x = i;
			break; // 적절한 컬럼을 찾았으면 더 이상 반복할 필요 없음
		}
	}

	for (int j = 0; j < AtlasRow; ++j) {
		// 행 인덱스 검사
		if (onerow * j <= row && onerow * (j + 1) > row) {
			residx.y = j;
			break; // 적절한 행을 찾았으면 더 이상 반복할 필요 없음
		}
	}

	if (onecol != -1 && onerow != -1)
	IsSetIdx = true;

	return residx;
}

void CSubAnimator2DUI::AnimClear()
{
	LeftTop.x = 0; LeftTop.y = 0;
	Offset.x = 0; Offset.y = 0;
	Background.x = 0; Background.y = 0;
	Duration = 0;
	CurFrmNum = -1;
	frmcount = 0;
	Animation_Key = ' ';

	vector<tAnimFrm> temp;
	swap(temp, tm_vecFrm);

	if(OneAnim != nullptr)
	{
		OneAnim = nullptr;
	}
}

void CSubAnimator2DUI::FloatAnimStruct()
{
	//frm 구조체 채우기
	float textLeftTop[2] = { LeftTop.x ,LeftTop.y };
	if (Fullfrmidx.x != -1 && Fullfrmidx.y != -1)
	{
		textLeftTop[0] = Fullfrmidx.x * OneFrmSize.x;
		textLeftTop[1] = Fullfrmidx.y * OneFrmSize.y;

		LeftTop.x = textLeftTop[0];
		LeftTop.y = textLeftTop[1];
	}
	ImGui::Text("LeftTop: (%.1f, %.1f)", textLeftTop[0], textLeftTop[1]);



	float textOffset[2] = { Offset.x, Offset.y };
	ImGui::InputFloat2("Offset", textOffset);

	Offset.x = textOffset[0];
	Offset.y = textOffset[1];

	float textBackground[2] = { Background.x, Background.y };
	ImGui::InputFloat2("Background", textBackground);

	Background.x = textBackground[0];
	Background.y = textBackground[1];

	float textduration = Duration;
	ImGui::InputFloat("Duration", &textduration);

	Duration = textduration;

	float textPadding[2] = { Padding.x, Padding.y };
	ImGui::InputFloat2("Padding", textPadding);

	Padding.x = textPadding[0];
	Padding.y = textPadding[1];

	if (ImGui::InputText("Animation Key", ShowAnimKey, IM_ARRAYSIZE(ShowAnimKey)))
	{
		Animation_Key = ToWString(ShowAnimKey);

	}
	ImGui::Text("Current Input: %s", ShowAnimKey);
}

void CSubAnimator2DUI::FloatFrmStruct()
{

	//frm 구조체 채우기

	float textOffset[2] = {
		tm_vecFrm[CurFrmNum].vOffset.x * m_AtlasTex->GetWidth(),
		tm_vecFrm[CurFrmNum].vOffset.y * m_AtlasTex->GetHeight()
	};

	if (ImGui::InputFloat2("Offset", textOffset))
	{
		tm_vecFrm[CurFrmNum].vOffset.x = textOffset[0] / (float)m_AtlasTex->GetWidth();
		tm_vecFrm[CurFrmNum].vOffset.y = textOffset[1] / (float)m_AtlasTex->GetHeight();

	}

	float textBackground[2] = { tm_vecFrm[CurFrmNum].vBackground.x * m_AtlasTex->GetWidth(),
								tm_vecFrm[CurFrmNum].vBackground.y * m_AtlasTex->GetHeight() };

	if (ImGui::InputFloat2("Background", textBackground))
	{
		tm_vecFrm[CurFrmNum].vBackground.x = textBackground[0] / (float)m_AtlasTex->GetWidth();
		tm_vecFrm[CurFrmNum].vBackground.y = textBackground[1] / (float)m_AtlasTex->GetHeight();
	}



	float textduration = tm_vecFrm[CurFrmNum].Duration;
	ImGui::InputFloat("Duration", &textduration);

	tm_vecFrm[CurFrmNum].Duration = textduration;

	if (ImGui::InputText("Animation Key", ShowAnimKey, IM_ARRAYSIZE(ShowAnimKey)))
	{
		Animation_Key = ToWString(ShowAnimKey);
	}
}

void CSubAnimator2DUI::DrawGrid(ImVec2 ImgPosition, ImVec2 _ImgSize, Vec2 _Padding, int _ColRow[2])
{
	int Acol = _ColRow[0];
	int Arow = _ColRow[1];

	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImVec2 startPos = { ImgPosition.x, ImgPosition.y }; // 그리드 시작 위치
	ImVec2 endPos = { ImgPosition.x + _ImgSize.x, ImgPosition.y + _ImgSize.y }; // 그리드 종료 위치
	ImU32 lineColor = IM_COL32(255, 255, 255, 255); // 선 색상
	float gridSpacingX = (1000 - _Padding.x) / Acol; // 수정된 수직선 간격 계산
	float gridSpacingY = (500 - _Padding.y) / Arow; // 수정된 수평선 간격 계산

	// 수직선 그리기
	for (int col = 0; col <= Acol; ++col)
	{
		float x = startPos.x + col * gridSpacingX; // 수정된 x 위치 계산
		drawList->AddLine(ImVec2(x, startPos.y), ImVec2(x, endPos.y), lineColor);
	}

	// 수평선 그리기
	for (int row = 0; row <= Arow; ++row)
	{
		float y = startPos.y + row * gridSpacingY; // 수정된 y 위치 계산
		drawList->AddLine(ImVec2(startPos.x, y), ImVec2(endPos.x, y), lineColor);
	}
}

void CSubAnimator2DUI::LoadAtlasButton(const char* BtnName, ImVec2 _Size)
{

	if (ImGui::Button(BtnName, _Size))
	{
		// 경로 찾기
		wstring NewFilePath = LoadFile();
		FilePath = MakePath(NewFilePath);

		// 키 찾기
		wstring NewKey;
		NewKey = MakeKey(FilePath);

		m_AtlasTex->Clear(10);
		m_AtlasTex = nullptr;
		Ptr<CTexture> temp = CAssetMgr::GetInst()->Load<CTexture>(NewKey, FilePath.c_str());
		m_AtlasTex = temp;

	}
}

void CSubAnimator2DUI::AddFrmButton(const char* BtnName, ImVec2 _Size)
{
	if (ImGui::Button(BtnName, _Size))
	{
		tAnimFrm temp = {};

		temp.vSlice = Vec2((OneFrmSize.x - (Padding.x/ AtlasCol))  / (float)m_AtlasTex->GetWidth(), (OneFrmSize.y - (Padding.y / AtlasRow)) / (float)m_AtlasTex->GetHeight());

		Vec2 TempLeftTop = LeftTop - Padding;

		if (TempLeftTop.x < 0.f)
			TempLeftTop.x = 0.f;

		if (LeftTop.y == 0)
			TempLeftTop.y = 0;

		float tLeftTopx = TempLeftTop.x;
		float tLeftTopy = TempLeftTop.y;

		temp.vLeftTop = Vec2{ tLeftTopx / (float)m_AtlasTex->GetWidth(), tLeftTopy / (float)m_AtlasTex->GetHeight() };
		temp.vOffset = Vec2(Offset.x / (float)m_AtlasTex->GetWidth(), Offset.y / (float)m_AtlasTex->GetHeight());
		temp.vBackground = Vec2(Background.x / (float)m_AtlasTex->GetWidth(), Background.y / (float)m_AtlasTex->GetHeight());
		temp.Duration = Duration;

		

		tm_vecFrm.push_back(temp);

		// 현재 프레임을 띄우기 위해 시작이 -1, 1를 만들면 0이 된다.
		++CurFrmNum;

		//첫 번째 0을 만들면 다음 프레임은 1, 새로 추가될 프레임의 숫자
		++frmcount;
	}
}

void CSubAnimator2DUI::PlayPreview()
{
	nowacctime += CTimeMgr::GetInst()->GetEngineDeltaTime();
	for (int i = 0; i < OneAnim->GetAnimFrm().size(); ++i)
	{
		if (tm_vecFrm[now].Duration < nowacctime)
		{
			++now;
			if (tm_vecFrm.size() <= now)
			{
				now = (int)tm_vecFrm.size() - 1;
				PreviewStop = true;
			}
			nowacctime = 0.f;
		}
	}
}

void CSubAnimator2DUI::SaveNewAnim()
{
	wstring strAnimPath = CPathMgr::GetContentPath();
	wstring AnimFolder = L"animation\\";
	strAnimPath += AnimFolder;
	strAnimPath += Animation_Key;

	ofstream temp(strAnimPath);

	if(temp.is_open())
	{
	OneAnim->SetAtlas(m_AtlasTex);
	OneAnim->SaveToFile(temp);
	}
}

void CSubAnimator2DUI::LoadAnim()
{
	CGameObject* pTarget = nullptr;
	pTarget = Super->GetTargetObj();
	CAnim* pAnim = new CAnim;

	wstring animname = L" ";
	animname = LoadFile();

	if (!exists(animname))
	{
		ImGui::EndTabItem();
		ImGui::EndTabBar();
		ImGui::End();
		return;
	}
	else
	{
		ifstream pFile;
		pFile.open(animname);

		pAnim->LoadFromFile(pFile);
		pAnim->SetAnimator(pTarget->Animator2D());

		CAnimator2D* pTargetAnimator2D = pTarget->Animator2D();

		pTargetAnimator2D->AddAnimtoMap(pAnim);


	}
}

