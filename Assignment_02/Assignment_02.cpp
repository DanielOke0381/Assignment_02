#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

#define PRE_RELEASE

// Define the STUDENT_DATA struct to store student names and email addresses
struct STUDENT_DATA {
    string firstName;
    string lastName;
    string email;
};

int main() {
    // Print build version status (Standard vs. Pre-Release)
#ifdef PRE_RELEASE
    cout << "Application is running PRE-RELEASE source code." << endl;
#else
    cout << "Application is running STANDARD source code." << endl;
#endif

    // Container to store parsed student objects
    vector<STUDENT_DATA> studentList;

    // Target text file containing student names (FirstName,LastName format)
    string filename = "StudentData.txt";

    // Open file stream
    ifstream inputFile(filename);

    // Verify file opened successfully
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open input file -> " << filename << endl;
        return 1;
    }
    else {
        cout << "Successfully opened file: " << filename << endl;
    }

    string line;
    // Read the file line by line and parse comma-separated fields
    while (getline(inputFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        STUDENT_DATA student;

        // Parse comma-separated values: FirstName,LastName
        getline(ss, student.firstName, ',');
        getline(ss, student.lastName, ',');

        studentList.push_back(student);
    }

    inputFile.close();

    cout << "Successfully parsed " << studentList.size() << " student records." << endl;

    // Print loaded student data ONLY when compiled under Debug mode
#ifdef _DEBUG
    cout << "\n==================================================" << endl;
    cout << "          [DEBUG MODE] Loaded Student Data        " << endl;
    cout << "==================================================" << endl;

    for (const auto& student : studentList) {
        cout << "Name: " << student.firstName << " " << student.lastName << endl;
    }

    cout << "==================================================\n" << endl;
#endif

    // Read email data and merge ONLY in Release mode (#ifndef _DEBUG)
#ifndef _DEBUG
    string emailFilename = "StudentData_Emails.txt";
    ifstream emailFile(emailFilename);

    if (!emailFile.is_open()) {
        cerr << "Error: Unable to open email file -> " << emailFilename << endl;
        return 1;
    }

    size_t index = 0;
    string emailLine;

    // Read emails and assign to corresponding student records
    while (getline(emailFile, emailLine) && index < studentList.size()) {
        if (!emailLine.empty()) {
            studentList[index].email = emailLine;
            index++;
        }
    }

    emailFile.close();

    cout << "\n==================================================" << endl;
    cout << "        [RELEASE MODE] Full Student Roster        " << endl;
    cout << "==================================================" << endl;

    for (const auto& student : studentList) {
        cout << "Name: " << student.firstName << " " << student.lastName
            << " | Email: " << student.email << endl;
    }

    cout << "==================================================\n" << endl;
#endif

    return 0;
}