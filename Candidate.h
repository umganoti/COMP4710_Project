#ifndef CANDIDATE_H
#define CANDIDATE_H


class Candidate
{
    private:
        int* m_tmv;
        int m_lmv;

    public:
        Candidate(int lmv, int tmv_size);
        int get_lmv() { return m_lmv; }
        int* get_tmv() { return m_tmv; }

};

#endif // CANDIDATE_H
