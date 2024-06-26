#pragma once
#include "CComponent.h"

#include "CTexture.h"

class CAnim;


class CAnimator2D :
    public CComponent
{
private:
    map<wstring, CAnim*>    m_mapAnim;
    CAnim*                  m_CurAnim;
    bool                    m_bRepeat;

public:
    virtual void finaltick() override;

    void UpdateData();
    static void Clear();

    // _LeftTop, _SliceSize, _Offset : Pixel Unit
    void Create(const wstring& _strKey, Ptr<CTexture> _AltasTex, Vec2 _LeftTop, Vec2 _vSliceSize, Vec2 _OffsetSize, Vec2 _Background, int _FrmCount, float _FPS);
    void Create(const wstring& _strKey, CAnim* Anim);

    CAnim* GetCurAnim() { return m_CurAnim; }
    void AddAnimtoMap(CAnim* _Anim);
    map<wstring, CAnim*>* GetAnimmap() { return &m_mapAnim; }

    CAnim* FindAnim(const wstring& _strAnimName);
    void Play(const wstring& _strAnimName, bool _bRepeat = true);

    void PlayModule(const wstring& _strAnimName, int& count);

    virtual void SaveToFile(ofstream& _File) override;
    virtual void LoadFromFile(ifstream& _File) override;
    CLONE(CAnimator2D);
public:
    CAnimator2D();
    CAnimator2D(const CAnimator2D& _OriginAnimator);
    ~CAnimator2D();
};

