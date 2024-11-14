#include <iostream>

using namespace std;

class emp {
private:
    string name;
    int empid;
    float salary;

public:
    void getsalary(){
        cout << "Specify your name" << endl;
        cin >> name;
        cout << "Employee ID"<< endl;
        cin >> empid;
        cout << "salary"<<endl;
        cin>>salary;
    }
    void performace(){
        cout << "Employee details: " << endl << "Name: " << name << endl << "ID: " << empid << endl << "Salary: " << salary << endl;
        if(salary >= 100000.0){
            cout << "Performance score: 10" << endl;
        }
        else{
            float p = salary / 10000.0;
            cout << "Performance score: " << p << endl;
        }
    }
};

int main(){
    emp e1;

    e1.getsalary();
    e1.performace();
}
