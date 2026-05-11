#include "ScreeningManager.h"
#include "ResumeParser.h"
#include "ITCandidate.h"
#include "NonITCandidate.h"
 
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <map>
#include <stdexcept>

using namespace std;
struct Result {
    string cid;
    string jobId;
    double score;
    int rank;
};
 
 
bool compareRank(const Result &a, const Result &b) {
    return a.rank < b.rank;
}
 
 
void ScreeningManager::loadResumes() {
    ResumeParser::parseAll();
}
 
 

 
void ScreeningManager::loadJobs() {
    try {
        ifstream fin("job_descriptions.csv");
 
        if (!fin) {
            throw runtime_error("job_descriptions.csv not found");
        }
 
        string line;
        int index = 1;
        jobs.clear();
 
        cout << "\nAvailable Jobs:\n";
 
        while (getline(fin, line)) {
 
            if (line.empty())
                continue;
 
            JobDescription job;
            job.loadFromCSV(line);
            jobs[index] = job;
 
            cout << index << ". "
                 << job.getJobID()
                 << " - "
                 << job.getTitle() << endl;
 
            index++;
        }
 
        fin.close();
    }
    catch (exception &e) {
        cout << "\nError loading jobs: " << e.what() << endl;
    }
}
 
 
 
int ScreeningManager::selectJob() {
 
    int choice;
    cout << "\nEnter job number: ";
    cin >> choice;
 
    if (jobs.find(choice) == jobs.end()) {
        cout << "\nInvalid selection\n";
        return -1;
    }
 
    return choice;
}
void ScreeningManager::screen(const JobDescription &job) {
 
    ifstream fin("candidates.csv");
    if (!fin) {
        cout << "\nError: candidates.csv not found\n";
        return;
    }
 
    ofstream fout("screening_results.csv");
    fout << "ResultID,CandidateID,JobID,Score,Rank\n";
 
    vector<Candidate*> list;
    map<string, string> emailMap;  
 
    string line;
    getline(fin, line);
 
    while (getline(fin, line)) {
 
        if (line.empty()) continue;
 
        stringstream ss(line);
 
        string id, name, email, phone, expStr, skillsStr, resumeFile;
 
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, phone, ',');
        getline(ss, expStr, ',');
        getline(ss, skillsStr, ',');
        getline(ss, resumeFile);
 
       
        emailMap[id] = email;
 
   
        if (!skillsStr.empty() && skillsStr[0] == '"')
            skillsStr.erase(0, 1);
 
        if (!skillsStr.empty() && skillsStr[skillsStr.length() - 1] == '"')
            skillsStr.erase(skillsStr.length() - 1, 1);
 
        Candidate* c;
 
        if (skillsStr.find("C++") != string::npos ||
            skillsStr.find("Java") != string::npos ||
            skillsStr.find("Python") != string::npos)
            c = new ITCandidate();
        else
            c = new NonITCandidate();
 
        int exp = atoi(expStr.c_str());
        c->setDetails(id, name, exp);
 
        stringstream skillStream(skillsStr);
        string skill;
 
        while (getline(skillStream, skill, ',')) {
 
            while (!skill.empty() && skill[0] == ' ')
                skill.erase(0, 1);
 
            while (!skill.empty() && skill[skill.length() - 1] == ' ')
                skill.erase(skill.length() - 1, 1);
 
            c->addSkill(skill);
        }
 
        c->calculateScore(job);
        list.push_back(c);
    }
 
    fin.close();
 
   
    sort(list.begin(), list.end(), CompareScore());
 
 
    cout << "\n=========== SCREENING RESULTS ===========\n\n";
 
    cout << left
         << setw(8)  << "ID"
         << setw(20) << "Name"
         << setw(28) << "Email"
         << setw(10) << "Score"
         << setw(8)  << "Rank"
         << setw(10) << "JobID"
         << endl;
 
    cout << "--------------------------------------------------------------------------\n";
 
    int rank = 1;
    int rid = 1;
    double totalScore = 0;
 
    for (size_t i = 0; i < list.size(); i++) {
 
        fout << "R" << rid++ << ","
             << list[i]->getId() << ","
             << job.getJobID() << ","
             << list[i]->getScore() << ","
             << rank << "\n";
        cout << left
             << setw(8)  << list[i]->getId()
             << setw(20) << list[i]->getName()
             << setw(33) << emailMap[list[i]->getId()]  
             << setw(10) << list[i]->getScore()
             << setw(8)  << rank
             << setw(10) << job.getJobID()
             << endl;
 
        totalScore += list[i]->getScore();
        rank++;
    }
 
    fout.close();
 
    double avg = (list.empty()) ? 0 : totalScore / list.size();
 
    cout << "\nScreening completed successfully\n";
    cout << "Average Score: " << avg << endl;
 
   
    for (size_t i = 0; i < list.size(); i++)
        delete list[i];
}
 
void ScreeningManager::shortlist(int topN) {
 
    ifstream fin("screening_results.csv");
    if (!fin) {
        cout << "\nError: screening_results.csv not found\n";
        return;
    }
 
    vector<Result> results;
    string line;
 
    getline(fin, line); // skip header
 
    while (getline(fin, line)) {
 
        if (line.empty()) continue;
 
        stringstream ss(line);
        Result r;
        string rid, scoreStr, rankStr;
 
        getline(ss, rid, ',');
        getline(ss, r.cid, ',');
        getline(ss, r.jobId, ',');
        getline(ss, scoreStr, ',');
        getline(ss, rankStr);
 
        r.score = atof(scoreStr.c_str());
        r.rank  = atoi(rankStr.c_str());
 
        results.push_back(r);
    }
 
    fin.close();
    sort(results.begin(), results.end(), compareRank);
 
    //  APPEND MODE  keeps old + new data
    ofstream fout("shortlist.log", ios::app);
 
    time_t now = time(0);
    string timeStr = ctime(&now);
    timeStr.erase(timeStr.find('\n')); 
 
    /* ================= WRITE TO FILE (HISTORY) ================= */
    fout << "================================================\n";
    fout << " Shortlist Generated On : " << timeStr << "\n";
    fout << "================================================\n";
 
    /* ================= SHOW ONLY CURRENT SHORTLIST IN TERMINAL ====*/
    cout << "\n============= CURRENT SHORTLIST =============\n";
    cout << "Generated On : " << timeStr << "\n";
    cout << "--------------------------------------------\n";
 
    int count = 0;
    int displayRank = 1;
 
    for (size_t i = 0; i < results.size() && count < topN; i++) {
 
        if (results[i].score > 0) {
 
            //  TERMINAL only current run
            cout << "Rank " << displayRank
                 << " | ID: " << results[i].cid
                 << " | Score: " << results[i].score << endl;
 
            //  FILE  append (history)
            fout << "Rank " << displayRank
                 << " | ID: " << results[i].cid
                 << " | Score: " << results[i].score << endl;
 
            displayRank++;
            count++;
        }
    }
 
    fout << "\n"; 
    fout.close();
 
    cout << "--------------------------------------------\n";
    cout << "[SUCCESS] Shortlist stored successfully\n";
}
 
 
void ScreeningManager::backup() {
 
    ifstream fin("candidates.csv");
 
    if (!fin) {
        cout << "\nError: candidates.csv not found\n";
        return;
    }
 
    ofstream fout("backup.dat");
 
    string line;
 
    while (getline(fin, line))
        fout << line << endl;
 
    fin.close();
    fout.close();
 
    cout << "\nBackup completed successfully\n";
}
 
 
 
