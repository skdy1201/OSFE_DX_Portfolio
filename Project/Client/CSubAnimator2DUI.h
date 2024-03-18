#pragma once
#include "Animator2DUI.h"
#include <Engine/CAnim.h>

class Animator2DUI;

class CSubAnimator2DUI :
    public UI
{
    virtual void render_update() override;


private:
    //�θ� ui
    Animator2DUI* Super;

    // object
    CGameObject* m_TargetObject;


    //�ؽ���
    Ptr<CTexture> m_AtlasTex;
    ComPtr<ID3D11ShaderResourceView> m_TextureView;

    wstring FilePath;

    //��Ʋ�� ����
    ImVec2 AtlasPosition;
    ImVec2 RealAtlasPixel;
    ImVec2 PrintAtlasSize;

    int AtlasCol;
    int AtlasRow;
    bool IsSetIdx;

    ImVec2 Padding;
   
    //������ ����
    ImVec2 FramePosition;
    Vec2 OneFrmSize;
    Vec2 Fullfrmidx;
    Vec2 LeftTop;
    Vec2 Offset;
    Vec2 Background;
    int frmcount;
    float Duration;


    CAnim* OneAnim;
    CAnimator2D* TargetAnimator2D;
    vector<tAnimFrm>   tm_vecFrm;

	wstring Animation_Key;
    char ShowAnimKey[128];

    //������ ����
    int CurFrmNum;

    // ������ ����
    bool PreviewStop;
    int now;
    float nowacctime;
private:
    wstring LoadFile();
    wstring MakePath(wstring FullPath);
    wstring MakeKey(wstring FullPath);

    ImVec2 CheckIndex(float col, float row);

    void AnimClear();

    void FloatAnimStruct();
    void FloatFrmStruct();
    void DrawGrid(ImVec2 ImgPosition, ImVec2 _ImgSize, ImVec2 _Padding, int _ColRow[2]);
    void LoadAtlasButton(const char* BtnName, ImVec2 _Size);
    void AddFrmButton(const char* BtnName, ImVec2 _Size);
    void PlayPreview();
    void SaveNewAnim();
    void LoadAnim();


public:
    CSubAnimator2DUI(Animator2DUI* Parent);
    ~CSubAnimator2DUI();

};

