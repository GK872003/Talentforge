
#include "ResumeParser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>   
 
using namespace std;
 
string trim(string s){
 
    if(s.length() == 0)
        return s;
 
    // remove leading spaces
    while(s.length() > 0 && isspace(s[0])){
        s.erase(0,1);
    }
 
    // remove trailing spaces
    while(s.length() > 0 && isspace(s[s.length()-1])){
        s.erase(s.length()-1,1);
    }
 
    return s;
}
 
 
// Parse all resumes
void ResumeParser::parseAll(){
 
    ofstream fout("candidates.csv");
 
    if(!fout){
        cout << "[ERROR] Unable to create candidates.csv\n";
        return;
    }

    fout << "CandidateID,Candidate Name,Email,Phone,Experience,Skills,ResumeFile\n";
 
    int i = 1;
 
    while(true){
 
        stringstream filepath;
        filepath << "resumes/resume" << i << ".txt";
 
        ifstream fin(filepath.str().c_str());
 
        if(!fin) break;
 
        string line;
        string name = "", email = "", phone = "", exp = "", skills = "";
 
        while(getline(fin, line)){
 
            if(line.find("Candidate Name:") != string::npos)
                name = trim(line.substr(line.find(":") + 1));
 
            else if(line.find("Email:") != string::npos)
                email = trim(line.substr(line.find(":") + 1));
 
            else if(line.find("Phone:") != string::npos)
                phone = trim(line.substr(line.find(":") + 1));
 
            else if(line.find("Experience:") != string::npos){
                string temp = line.substr(line.find(":") + 1);
                exp = trim(temp.substr(0, temp.find("years")));
            }
 
            else if(line.find("Skills:") != string::npos)
                skills = trim(line.substr(line.find(":") + 1));
        }
 
        
        //string resumeFileName = "resume" + to_string(i) + ".txt";
        stringstream ss;
        ss<<"resume"<<i<<".txt";
        string resumeFileName=ss.str();
 
      
        fout << "C" << i << ","
             << name << ","
             << email << ","
             << phone << ","
             << exp << ","
             << "\"" << skills << "\","   
             << resumeFileName
             << "\n";
 
        fin.close();
        i++;
    }
 
    fout.close();
 
    cout << "\n[SUCCESS] Resumes parsed successfully and saved to candidates.csv\n";
}



