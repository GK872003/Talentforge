#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <string>
#include <set>
#include "JobDescription.h"

class Candidate {
protected:
    std::string id, name;
    int experience;
    std::set<std::string> skills;
    double score;

public:
    Candidate();
    virtual ~Candidate();

    void setDetails(std::string id, std::string name);
    void setDetails(std::string id, std::string name, int exp);

    void addSkill(const std::string&);

    std::string getId() const;
    std::string getName() const;
    int getExperience() const;
    double getScore() const;

    virtual void calculateScore(const JobDescription&) = 0;

    friend void showCandidate(const Candidate&);
};

#endif


