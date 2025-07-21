#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const string FILE_NAME = "hospital.txt";

void addPatient() {
    ofstream file(FILE_NAME, ios::app);
    string name, disease;
    int age;

    cout << "Enter Patient Name: ";
    getline(cin >> ws, name);
    cout << "Enter Age: ";
    cin >> age;
    cin.ignore();
    cout << "Enter Disease: ";
    getline(cin, disease);

    file << name << " | " << age << " | " << disease << endl;
    file.close();

    cout << "Patient added successfully!" << endl;
}

void viewPatients() {
    ifstream file(FILE_NAME);
    if (!file) {
        cout << "No patient records found." << endl;
        return;
    }

    string line;
    cout << "\nPatient Records:\n";
    cout << "-------------------------------------------------------------\n";
    cout << left << setw(20) << "Name" << setw(10) << "Age" << setw(20) << "Disease" << endl;
    cout << "-------------------------------------------------------------\n";

    while (getline(file, line)) {
        size_t pos1 = line.find(" | ");
        size_t pos2 = line.find(" | ", pos1 + 3);

        if (pos1 == string::npos || pos2 == string::npos) continue;

        string name = line.substr(0, pos1);
        string ageStr = line.substr(pos1 + 3, pos2 - (pos1 + 3));
        string disease = line.substr(pos2 + 3);

        try {
            int age = stoi(ageStr);
            cout << left << setw(20) << name << setw(10) << age << setw(20) << disease << endl;
        } catch (...) {
            continue;
        }
    }

    file.close();
}

void searchPatient() {
    ifstream file(FILE_NAME);
    if (!file) {
        cout << "No patient records found." << endl;
        return;
    }

    string searchName, line;
    bool found = false;

    cout << "Enter Patient Name to Search: ";
    getline(cin >> ws, searchName);

    while (getline(file, line)) {
        if (line.find(searchName) != string::npos) {
            cout << "Patient Found: " << line << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Patient not found." << endl;
    }

    file.close();
}

void deletePatient() {
    ifstream file(FILE_NAME);
    ofstream temp("temp.txt");
    if (!file || !temp) {
        cout << "Error opening files!" << endl;
        return;
    }

    string deleteName, line;
    bool found = false;

    cout << "Enter Patient Name to Delete: ";
    getline(cin >> ws, deleteName);

    while (getline(file, line)) {
        if (line.find(deleteName) != string::npos) {
            cout << "Deleted: " << line << endl;
            found = true;
            continue;
        }
        temp << line << endl;
    }

    file.close();
    temp.close();

    if (found) {
        if (remove(FILE_NAME.c_str()) == 0) {
            if (rename("temp.txt", FILE_NAME.c_str()) == 0) {
                cout << "Patient deleted successfully." << endl;
            } else {
                cout << "Error: Could not rename temp file." << endl;
            }
        } else {
            cout << "Error: Could not delete original file." << endl;
        }
    } else {
        remove("temp.txt");
        cout << "Patient not found." << endl;
    }
}

int main() {
    int choice;
    do {
        cout << "\nHospital Management System\n";
        cout << "1. Add Patient\n";
        cout << "2. View All Patients\n";
        cout << "3. Search Patient by Name\n";
        cout << "4. Delete Patient by Name\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2:
                viewPatients();
                break;
            case 3:
                searchPatient();
                break;
            case 4:
                deletePatient();
                break;
            case 5:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice." << endl;
        }

    } while (choice != 5);

    return 0;
}

