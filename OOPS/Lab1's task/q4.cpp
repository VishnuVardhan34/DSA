#include <iostream>

using namespace std;

class date {
private:
    int day;
    int month;
    int year;
    int flag = 0; // Moved flag initialization to the private section

public:
    void getdateinput() {
        cout << "Enter day, month, year respectively: ";
        cin >> day >> month >> year;
        checkleapyear(year);
        checkdate();
    }

    void checkleapyear(int year) {
        if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) {
            flag = 1;
        }
    }

    void checkdate() {
        if (month < 1 || month > 12) {
            cout << "Invalid Date: Month out of range" << endl;
            return;
        }

        if (day < 1 || day > 31) {
            cout << "Invalid Date: Day out of range" << endl;
            return;
        }

        if (month == 2) {
            if ((flag == 1 && day > 29) || (flag == 0 && day > 28)) {
                cout << "Invalid Date: Day out of range for February" << endl;
                return;
            }
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            if (day > 30) {
                cout << "Invalid Date: Day out of range for the month" << endl;
                return;
            }
        }

        cout << "Date is valid" << endl;
    }
};

int main() {
    date check1;
    check1.getdateinput();
    return 0;
}
