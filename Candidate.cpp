#include "Candidate.h"

Candidate::Candidate(int lmv, int tmv_size)
{
    m_lmv = lmv;
    m_tmv = new int[tmv_size];
}

