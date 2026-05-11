#ifndef NONITCANDIDATE_H
#define NONITCANDIDATE_H

#include "Candidate.h"

class NonITCandidate : public Candidate {

public:
    void calculateScore(const JobDescription&);
};

#endif


