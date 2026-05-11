#ifndef SCREENINGMANAGER_H
#define SCREENINGMANAGER_H

#include <vector>
#include <map>
#include <queue>

#include "Candidate.h"
#include "Comparator.h"
#include "JobDescription.h"

class ScreeningManager {

private:

    std::vector<Candidate*> candidates;

    std::map<int, JobDescription> jobs;

    std::priority_queue<
        Candidate*,
        std::vector<Candidate*>,
        CompareScore
    > rankingQueue;

public:

    void loadResumes();

    void loadJobs();

    int selectJob();

    void screen(const JobDescription&);

    void shortlist(int);
    
    void displayShortlistedReport();

    void backup();
};

#endif



