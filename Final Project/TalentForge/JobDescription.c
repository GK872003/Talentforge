#include "JobDescription.h"
#include <sstream>
#include <cstdlib>
 
void JobDescription::loadFromCSV(const std::string& line) {
    std::stringstream ss(line);
    skills.clear();
 
    getline(ss, jobID, ',');
    getline(ss, title, ',');
 
    std::string token;
 
    while(getline(ss, token, ',')) {
        int pos = token.find(':');
        std::string skill = token.substr(0, pos);
        int weight = atoi(token.substr(pos+1).c_str());
        skills[skill] = weight;
    }
}
 
const std::map<std::string,int>& JobDescription::getSkills() const {
    return skills;
}
 
std::string JobDescription::getJobID() const { return jobID; }
std::string JobDescription::getTitle() const { return title; }
 
