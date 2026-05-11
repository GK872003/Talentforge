#include "ITCandidate.h"

void ITCandidate::calculateScore(const JobDescription& job){
    score=0;
    std::map<std::string,int> req=job.getSkills();

    for(std::map<std::string,int>::iterator it=req.begin(); it!=req.end(); ++it)
        if(skills.count(it->first))
            score+=it->second;

    score+=experience*2;
}


