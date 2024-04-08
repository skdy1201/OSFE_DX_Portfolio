#include "pch.h"
#include "CRandomMgr.h"

#include <random>
#include <Engine/CFontMgr.h>

CRandomMgr::CRandomMgr()
{
}

CRandomMgr::~CRandomMgr()
{
}

void CRandomMgr::GenNewSeed(UINT32 _seed)
{
    // 난수 생성 엔진 초기화를 위한 시드 생성
    m_seed = _seed;
    std::mt19937 gen(m_seed); // Mersenne Twister 난수 생성 엔진 초기화
    m_GenEngine = gen;
    std::uniform_int_distribution<> dis(0, RandomAccuracy - 1);
    m_DistGenerator = dis;
}

void CRandomMgr::SetSeed(UINT32 _seed)
{
    GenNewSeed(_seed);
}

void CRandomMgr::init()
{
    std::random_device rd; // 하드웨어 난수 생성기를 사용하여 시드 생성
    GenNewSeed(rd());
}

int CRandomMgr::GetRandom(int _bound)
{
    return  m_DistGenerator(m_GenEngine) % _bound;
}

bool CRandomMgr::RandomSucceed(int _probability, int _bound)
{
    return GETRANDOM(_bound) < _probability ? true : false;
}
