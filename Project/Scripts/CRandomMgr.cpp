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
    // ���� ���� ���� �ʱ�ȭ�� ���� �õ� ����
    m_seed = _seed;
    std::mt19937 gen(m_seed); // Mersenne Twister ���� ���� ���� �ʱ�ȭ
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
    std::random_device rd; // �ϵ���� ���� �����⸦ ����Ͽ� �õ� ����
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
