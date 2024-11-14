#include <iostream>
using namespace std;

class Student {
private:
    string name;
    int rollNumber;
    int marks;

public:
    Student() : name("Unknown"), rollNumber(0), marks(0) {}

    Student(string n, int r, int m) : name(n), rollNumber(r), marks(m) {}

    void display() const {
        cout << "Name: " << name << endl;
        cout << "Roll Number: " << rollNumber << endl;
        cout << "Marks: " << marks << endl;
    }
};

int main() {
    Student student1;
    Student student2("John Doe", 101, 85);

    cout << "Student 1 details (default constructor):" << endl;
    student1.display();

    cout << "\nStudent 2 details (parameterized constructor):" << endl;
    student2.display();

    return 0;
}
