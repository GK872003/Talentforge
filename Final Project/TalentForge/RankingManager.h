#ifndef RANKINGMANAGER_H
#define RANKINGMANAGER_H

#include <queue>
#include <vector>
#include "Candidate.h"

struct CompareScore {
    bool operator()(Candidate* a, Candidate* b) const {
        return a->getScore() < b->getScore();
    }
};

void generateShortlist(
    std::priority_queue<Candidate*, std::vector<Candidate*>, CompareScore>& pq
);

#endif


