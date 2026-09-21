#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Define the STUDENT_DATA struct to store student names
struct STUDENT_DATA {
    string firstName;
    string lastName;
};

int main() {
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

    return 0;
}