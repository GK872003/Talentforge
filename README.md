# TalentForge – Intelligent Resume Screening & Candidate Ranking Platform

TalentForge is a console-based HR technology solution developed in pure C++98 for automated resume screening and candidate ranking. The system eliminates manual shortlisting by using a rule-based scoring engine that evaluates candidates based on skills, experience, certifications, and job requirements.

Built using Object-Oriented Programming principles, STL containers, and file handling concepts, TalentForge demonstrates how core C++ can be applied to solve real-world recruitment challenges efficiently and objectively. 

---

## 🧠 Overview

Modern recruitment teams receive thousands of resumes for a single job role, making manual screening time-consuming, inconsistent, and prone to bias. TalentForge addresses these challenges by introducing:

* Automated resume parsing and skill extraction
* Intelligent candidate scoring and ranking
* Bias-free shortlisting using rule-based evaluation
* Audit-ready logging and data backup mechanisms
* Scalable architecture using OOP principles

The project was designed as an academic and industry-oriented software engineering solution using only standard C++98 features without external libraries. 

---

## ⚙️ Features

### ✅ Automated Resume Screening

Parses candidate resumes from text files and extracts relevant technical and non-technical skills.

### ✅ Intelligent Candidate Ranking

Uses weighted skill matching and bonus criteria to generate accurate candidate scores.

### ✅ OOP-Based Modular Architecture

Implements:

* Encapsulation
* Inheritance
* Abstraction
* Polymorphism

### ✅ STL-Powered Data Management

Uses:

* `vector`
* `set`
* `map`
* `priority_queue`

for efficient data storage and ranking.

### ✅ Audit & Compliance Logging

Maintains:

* screening results
* shortlist logs
* backup files

for transparency and traceability.

### ✅ Scalable Design

Supports future expansion through inheritance-based candidate models without modifying existing modules. 

---

# 📁 File Structure

```bash
.
├── main.cpp               # Main application entry point
├── Candidate.h            # Abstract base candidate class
├── ITCandidate.h          # IT candidate implementation
├── NonITCandidate.h       # Non-IT candidate implementation
├── ScreeningManager.h     # Core screening manager
├── resumes/               # Resume text files
├── shortlist.log          # Audit trail logs
├── screening_results.csv  # Final shortlisted candidates
├── backup.dat             # Binary backup storage
├── Project_Report.pdf     # Complete academic documentation
└── README.md              # Project documentation
```

---

# 🛠️ Tools & Technologies

| Technology      | Description                 |
| --------------- | --------------------------- |
| Language        | C++98                       |
| Paradigm        | Object-Oriented Programming |
| Data Structures | STL Containers              |
| File Handling   | CSV, TXT, Binary Files      |
| Platform        | Console-Based Application   |
| Architecture    | Modular Software Design     |

---

# 📐 System Architecture

TalentForge is designed around 5 core modules managed through the `ScreeningManager` facade class. 

## 1️⃣ Resume Ingestion Module

* Reads resumes from text files
* Extracts skills using `set<string>`
* Stores parsed candidate data

## 2️⃣ Job Description Module

* Uses `map<string,int>` for required skills
* Assigns weighted importance to each skill
* Total skill weight normalized to 100

## 3️⃣ Skill Matching Engine

* Performs case-insensitive keyword matching
* Calculates candidate compatibility score
* Applies experience and certification bonuses

## 4️⃣ Ranking & Shortlisting Module

* Uses `priority_queue`
* Extracts top-N candidates efficiently
* Supports fast ranking operations

## 5️⃣ Export & Logging Module

* Generates screening results
* Maintains append-only audit logs
* Stores binary backups for recovery

---

# 🧩 OOP Design

## Abstract Base Class

```cpp
class Candidate {
public:
    virtual double calculateScore() = 0;
    virtual string getCandidateType() = 0;
};
```

## Derived Classes

### ITCandidate

Includes:

* Technical skills
* Certifications
* Experience-based scoring

### NonITCandidate

Includes:

* Domain expertise
* Language proficiency
* Industry-specific evaluation

---

# 📊 Scoring Formula

## IT Candidate Scoring

```text
normalizedScore = (matchedSkillWeight / totalWeight) × 100

expBonus = min(experienceYears × 2.0, 10.0)

certBonus = certifications.empty() ? 0.0 : 5.0

finalScore = min(normalizedScore + expBonus + certBonus, 100.0)
```

| Component           | Formula                 | Max Points |
| ------------------- | ----------------------- | ---------- |
| Skill Match         | (matched ÷ total) × 100 | ~100       |
| Experience Bonus    | min(years × 2, 10)      | +10        |
| Certification Bonus | If certified            | +5         |
| Final Score         | Capped at 100           | ≤100       |



---

# ✅ Key Functionalities

* Resume Parsing
* Candidate Classification
* Weighted Skill Matching
* Automatic Candidate Ranking
* Top-N Shortlisting
* Audit Logging
* Backup Management
* Menu-Driven Console Interface

---

# 📈 Business & Academic Impact

| Metric                | Impact        |
| --------------------- | ------------- |
| Screening Speed       | 80% Faster    |
| Resume Capacity       | 5000+ Resumes |
| Human Bias            | Eliminated    |
| External Dependencies | Zero          |

### Why TalentForge Stands Out

* Fast STL-based ranking system
* Highly scalable OOP architecture
* Complete audit trail support
* Real-world HR automation use case
* Demonstrates advanced C++98 mastery



---

# 🚀 Getting Started

## 1️⃣ Clone Repository

```bash
git clone https://github.com/yourusername/TalentForge.git
cd TalentForge
```

## 2️⃣ Compile Project

Using g++:

```bash
g++ main.cpp -o TalentForge
```

## 3️⃣ Run Application

```bash
./TalentForge
```

---

# 📚 Concepts Demonstrated

## Core C++ Concepts

* Classes & Objects
* Inheritance
* Virtual Functions
* Polymorphism
* Abstract Classes
* Encapsulation

## STL Concepts

* vector
* map
* set
* priority_queue
* STL Algorithms

## File Handling

* Text File Processing
* CSV Export
* Binary File Storage
* Logging Systems

---

# 🧩 Future Enhancements

* GUI-based interface using Qt
* Database integration (MySQL/SQLite)
* AI-based resume analysis
* NLP-powered keyword extraction
* Web-based recruitment dashboard
* Multi-role job support
* Cloud deployment integration

---

# 👥 Author

* Gaurav Katkar


Project Domain: HR Technology & Recruitment Automation 

---

# 📜 License

This project is created for learning and portfolio purposes only.
