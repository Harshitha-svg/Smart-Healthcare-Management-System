#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// ------------------- Base User Class --------------------
class User {
protected:
    string name, mobile;
public:
    User(string n="", string m="") : name(n), mobile(m) {}
    virtual void display() = 0;
};

// ------------------- Patient Class --------------------
class Patient : public User {
public:
    string disease;

    Patient(string n="", string m="", string d="") :
        User(n,m), disease(d) {}

    void display() {
        cout << "Patient Name: " << name << "\nMobile: " << mobile
             << "\nDisease: " << disease << endl;
    }
};

// ------------------- Doctor Class --------------------
class Doctor : public User {
public:
    string specialization;

    Doctor(string n="", string m="", string s="") :
        User(n,m), specialization(s) {}

    void display() {
        cout << "Doctor Name: " << name
             << "\nSpecialization: " << specialization << endl;
    }
};

// ------------------- Appointment Class --------------------
class Appointment {
public:
    string patientName;
    string doctorName;
    string slot;

    Appointment(string p="", string d="", string s="") :
        patientName(p), doctorName(d), slot(s) {}
};

// ------------------- Hospital Manager --------------------
class Hospital {
    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;

public:

    // ----------------- Add Patient -----------------
    void addPatient() {
        string name, mobile, disease;

        cout << "Enter patient name: ";
        cin >> name;
        cout << "Enter mobile: ";
        cin >> mobile;
        cout << "Enter disease: ";
        cin >> disease;

        patients.push_back(Patient(name,mobile,disease));

        ofstream file("patients.txt", ios::app);
        file << name << " " << mobile << " " << disease << endl;
        file.close();

        cout << "Patient Registered Successfully!\n";
    }

    // ----------------- Add Doctor -----------------
    void addDoctor() {
        string name, mobile, spec;

        cout << "Enter doctor name: ";
        cin >> name;
        cout << "Enter mobile: ";
        cin >> mobile;
        cout << "Enter specialization: ";
        cin >> spec;

        doctors.push_back(Doctor(name,mobile,spec));

        ofstream file("doctors.txt", ios::app);
        file << name << " " << mobile << " " << spec << endl;
        file.close();

        cout << "Doctor Added Successfully!\n";
    }

    // ----------------- Search Doctor by specialization -----------------
    void searchDoctor() {
        string spec;
        cout << "Enter specialization: ";
        cin >> spec;

        for(auto &d : doctors) {
            if(d.specialization == spec) {
                cout << "\nDoctor Found:\n";
                d.display();
                return;
            }
        }
        cout << "No doctor found!\n";
    }

    // ----------- Appointment Backtracking ----------
    bool bookSlot(string slot) {
        for(auto &a : appointments)
            if(a.slot == slot) return false;
        return true;
    }

    void bookAppointment() {
        string pname, dname;
        string slot;
        cout << "Enter patient name: ";
        cin >> pname;
        cout << "Enter doctor name: ";
        cin >> dname;

        vector<string> sl = {"9AM", "11AM", "2PM", "4PM"};

        bool assigned = false;

        for(string s : sl) {
            if(bookSlot(s)) {
                slot = s;
                assigned = true;
                break;
            }
        }

        if(!assigned) {
            cout << "No Appointment Available!\n";
            return;
        }

        appointments.push_back(Appointment(pname,dname,slot));

        ofstream file("appointments.txt", ios::app);
        file << pname << " " << dname << " " << slot << endl;
        file.close();

        cout << "Appointment Fixed at: " << slot << endl;
    }

    // ------------------ Display Appointments ------------------
    void viewAppointments() {
        ifstream file("appointments.txt");
        string p,d,s;
        while(file >> p >> d >> s)
            cout << p << " -> " << d << " at " << s << endl;
        file.close();
    }
};

// ------------------------------------------------------------

int main() {
    Hospital h;
    int ch;

    while(1) {
        cout << "\n--- Smart Healthcare System ---\n";
        cout << "1. Register Patient\n";
        cout << "2. Add Doctor\n";
        cout << "3. Search Doctor by Specialization\n";
        cout << "4. Book Appointment\n";
        cout << "5. View Appointments\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> ch;

        switch(ch) {
            case 1: h.addPatient(); break;
            case 2: h.addDoctor(); break;
            case 3: h.searchDoctor(); break;
            case 4: h.bookAppointment(); break;
            case 5: h.viewAppointments(); break;
            case 6: exit(0);
            default: cout << "Invalid choice!";
        }
    }
}

