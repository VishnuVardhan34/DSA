#include <iostream>
#include <iomanip>
using namespace std;

class Time {
private:
    int hours;
    int minutes;

public:
    Time(int h = 0, int m = 0) : hours(h), minutes(m) {
        normalizeTime();
    }

    void normalizeTime() {
        if (minutes >= 60) {
            hours += minutes / 60;
            minutes %= 60;
        } else if (minutes < 0) {
            hours += (minutes - 59) / 60;
            minutes = (minutes % 60 + 60) % 60;
        }
        hours = (hours % 24 + 24) % 24;
    }

    Time operator+(const Time& other) const {
        Time result(hours + other.hours, minutes + other.minutes);
        result.normalizeTime();
        return result;
    }

    Time operator-(const Time& other) const {
        Time result(hours - other.hours, minutes - other.minutes);
        result.normalizeTime();
        return result;
    }

    friend ostream& operator<<(ostream& os, const Time& time) {
        os << setw(2) << setfill('0') << time.hours << ":"
           << setw(2) << setfill('0') << time.minutes;
        return os;
    }
};

int main() {
    int h1, m1, h2, m2;
    cout << "Enter the first time (hours and minutes): ";
    cin >> h1 >> m1;
    Time t1(h1, m1);
    cout << "Enter the second time (hours and minutes): ";
    cin >> h2 >> m2;
    Time t2(h2, m2);
    Time sum = t1 + t2;
    Time diff = t1 - t2;
    cout << "First time: " << t1 << endl;
    cout << "Second time: " << t2 << endl;
    cout << "Sum of times: " << sum << endl;
    cout << "Difference of times: " << diff << endl;
    return 0;
}

