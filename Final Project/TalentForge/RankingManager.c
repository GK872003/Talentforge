#include "RankingManager.h"
#include <fstream>

void generateShortlist(
    std::priority_queue<Candidate*, std::vector<Candidate*>, CompareScore>& pq)
{
    std::ofstream fout("shortlist.log");

    fout << "Rank,ID,Score\n";

    int rank = 1;
    while (!pq.empty()) {
        Candidate* c = pq.top();
        pq.pop();

        fout << rank << ","
             << c->getId() << ","
             << c->getScore() << "\n";

        rank++;
    }

    fout.close();
}

