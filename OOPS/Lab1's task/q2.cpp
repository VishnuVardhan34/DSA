#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int grade;
    string rollnumber;
    int marks;

public:
    void getInfo() {
        cout << "Student Name:" << endl;
        cin >> name;
        cout << "Class:" << endl;
        cin >> grade;
        cout << "Roll number:" << endl;
        cin >> rollnumber;
        cout << "Total marks (/1000):" << endl;
        cin >> marks;
    }

    void decideGrade() {
        if (marks > 950) {
            cout << "Report: A" << endl;
        } else if (marks > 800 && marks <= 950) {
            cout << "Report: B" << endl;
        } else if (marks > 650 && marks <= 800) {
            cout << "Report: C" << endl;
        } else {
            cout << "Report: F" << endl;
        }
    }
};

int main() {
    Student first;

    first.getInfo();

    first.decideGrade();
    return 0;
}
