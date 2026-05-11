#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <cstdlib>
#include "ScreeningManager.h"

using namespace std;

// ================= CLEAR SCREEN =================
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ================= PAUSE =================
void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// ================= MENU BOX =================
void showMenuBox() {

    int width = 80;
    int boxWidth = 50;
    int padding = (width-boxWidth)/2;

    string space(padding, ' ');

    cout << "\n";

        cout << "\n+==============================================================+\n";
        cout << "|           TALENTFORGE - Resume Screening Platform            |\n";
        cout << "|             TalentForge HR Solutions Pvt. Ltd.               |\n";
        cout << "+==============================================================+\n";
        cout << "| No | Menu Option                                             |\n";
        cout << "+----+---------------------------------------------------------+\n";
        cout << "| 1  | Resume Ingestion & Parsing                              |\n";
        cout << "| 2  | Job Description Management                              |\n";
        cout << "| 3  | Screen & Rank Candidates                                |\n";
        cout << "| 4  | View & Manage Shortlists                                |\n";
        cout << "| 5  | Analytics & Reports                                     |\n";
        cout << "| 6  | System Backup & Restore                                 |\n";
        cout << "| 7  | Exit                                                    |\n";
        cout << "+==============================================================+\n";


    cout << "\nEnter your choice (1-7): ";
}

// ================= DISPLAY FILE =================
void display(const char* fileName) {

    ifstream fin(fileName);

    if (!fin) {
        cout << "\n[ERROR] Unable to open file: " << fileName << endl;
        return;
    }

    string line;

    cout << "\n------------ " << fileName << " ------------\n";

    while (getline(fin, line)) {
        cout << line << endl;
    }

    cout << "-------------------------------------------\n";

    fin.close();
}


void displayDetailedReport() {
 
    ifstream fin1("candidates.csv");
    ifstream fin2("screening_results.csv");
 
    if (!fin1 || !fin2) {
        cout << "\n[ERROR] Required files not found.\n";
        return;
    }
 
    map<string, string> candidateNames;
    map<string, string> candidateEmails;   
 
    string line;
 
    getline(fin1, line); // skip header
 
    while (getline(fin1, line)) {
 
        stringstream ss(line);
 
        string id, name, email, phone, exp, skills, resume;
 
        //  Correct parsing
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, phone, ',');
        getline(ss, exp, ',');
        getline(ss, skills, ',');
        getline(ss, resume);
 
        candidateNames[id] = name;
        candidateEmails[id] = email;   
    }
 
    fin1.close();
 
    cout << "\n============================== CANDIDATE ANALYTICS REPORT =========================\n";
 
    cout << left
         << setw(6)  << "ID"
         << setw(20) << "Name"
         << setw(28) << "Email"   
         << setw(10) << "Score"
         << setw(8)  << "Rank"
         << setw(10) << "JobID"
         << endl;
 
    cout << "-----------------------------------------------------------------------------------\n";
 
    getline(fin2, line);  
    int count = 0;
    int topN = 10;
 
    while (getline(fin2, line) && count < topN) {
 
        stringstream ss(line);
 
        string rid, cid, jid, score, rank;
 
        getline(ss, rid, ',');
        getline(ss, cid, ',');
        getline(ss, jid, ',');
        getline(ss, score, ',');
        getline(ss, rank);
 
        cout << left
             << setw(6)  << cid
             << setw(20) << candidateNames[cid]
             << setw(33) << candidateEmails[cid]   
             << setw(10) << score
             << setw(8)  << rank
             << setw(10) << jid
             << endl;
 
        count++;
    }
 
    cout << "-----------------------------------------------------------------------------------\n";
 
    fin2.close();
    pauseScreen();
}



// ================= MAIN =================
int main() {

    ScreeningManager sm;
    int choice;

    do {

        clearScreen();   

        showMenuBox();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\n[ERROR] Invalid input!\n";
            pauseScreen();
            continue;
        }

        clearScreen();   // For Everytime FRESH PAGE

        switch (choice) {

        case 1:
            cout << "[INFO] Parsing resumes...\n";
            sm.loadResumes();
            display("candidates.csv");
            pauseScreen();
            break;

        case 2:
            cout << "[INFO] Loading job descriptions...\n";
            sm.loadJobs();
            pauseScreen();
            break;

        case 3: {
            cout << "[INFO] Screening candidates...\n";

            sm.loadJobs();

            int jobChoice = sm.selectJob();

            if (jobChoice == -1) {
                cout << "[ERROR] Invalid job selection.\n";
                pauseScreen();
                break;
            }

            ifstream fin("job_descriptions.csv");

            if (!fin) {
                cout << "[ERROR] job_descriptions.csv not found.\n";
                pauseScreen();
                break;
            }

            string line;
            int index = 1;
            JobDescription job;
            bool found = false;

            while (getline(fin, line)) {
                if (index == jobChoice) {
                    job.loadFromCSV(line);
                    found = true;
                    break;
                }
                index++;
            }

            fin.close();

            if (!found) {
                cout << "[ERROR] Job not found.\n";
                pauseScreen();
                break;
            }

            sm.screen(job);

            cout << "\n[INFO] Screening Results:\n";
            display("screening_results.csv");

            pauseScreen();
            break;
        }

        case 4:
            
              cout << "\n[INFO] Generating shortlist...\n";
              sm.shortlist(5);
            pauseScreen();
            break;

        case 5:
            cout << "[INFO] Displaying analytics/report...\n";
            displayDetailedReport();
            break;

        case 6:
            cout << "[INFO] Creating backup...\n";
            sm.backup();
            cout << "[SUCCESS] Backup stored successfully (backup.dat)\n";
            pauseScreen();
            break;

        case 7:
            clearScreen();
            cout << "\n";
            cout << "         Thank you for using TalentForge!\n";
            break;

        default:
            cout << "[ERROR] Invalid choice!\n";
            pauseScreen();
        }

    } while (choice != 7);

    return 0;
}





 


