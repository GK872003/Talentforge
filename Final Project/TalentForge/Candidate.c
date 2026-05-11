#include "Candidate.h"
#include <iostream>

Candidate::Candidate():experience(0),score(0){}
Candidate::~Candidate(){}

void Candidate::setDetails(std::string i,std::string n){ id=i; name=n; }
void Candidate::setDetails(std::string i,std::string n,int e){ id=i; name=n; experience=e; }

void Candidate::addSkill(const std::string& s){ skills.insert(s); }

std::string Candidate::getId() const { return id; }
std::string Candidate::getName() const { return name; }
int Candidate::getExperience() const { return experience; }
double Candidate::getScore() const { return score; }

void showCandidate(const Candidate& c){
    std::cout<<"ID:"<<c.id<<" Name:"<<c.name<<" Score:"<<c.score<<std::endl;
}


