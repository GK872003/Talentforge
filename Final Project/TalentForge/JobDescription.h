#ifndef JOBDESCRIPTION_H
#define JOBDESCRIPTION_H
 
#include <string>
#include <map>
 
class JobDescription {
    std::string jobID, title;
    std::map<std::string,int> skills;
 
public:
    void loadFromCSV(const std::string&);
    const std::map<std::string,int>& getSkills() const;
    std::string getJobID() const;
    std::string getTitle() const;
};
 
#endif


