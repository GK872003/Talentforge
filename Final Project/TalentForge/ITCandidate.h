#ifndef ITCANDIDATE_H
#define ITCANDIDATE_H

#include "Candidate.h"

class ITCandidate : public Candidate {

public:
    void calculateScore(const JobDescription&);
};

#endif

