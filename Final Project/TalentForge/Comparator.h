#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "Candidate.h"

struct CompareScore{
    bool operator()(Candidate* a, Candidate* b){
        return a->getScore() > b->getScore();
    }
};

#endif



