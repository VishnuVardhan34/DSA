#include <iostream>
using namespace std;

class Fraction {
private:
    int numerator;
    int denominator;

    int gcd(int a, int b) const {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    void simplify() {
        int divisor = gcd(numerator, denominator);
        numerator /= divisor;
        denominator /= divisor;
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    Fraction(int num = 0, int denom = 1) : numerator(num), denominator(denom) {
        if (denominator == 0) {
            cout << "Error: Denominator cannot be zero. Setting to 1." << endl;
            denominator = 1;
        }
        simplify();
    }

    Fraction operator+(const Fraction& other) const {
        int num = numerator * other.denominator + other.numerator * denominator;
        int denom = denominator * other.denominator;
        Fraction result(num, denom);
        result.simplify();
        return result;
    }

    Fraction operator-(const Fraction& other) const {
        int num = numerator * other.denominator - other.numerator * denominator;
        int denom = denominator * other.denominator;
        Fraction result(num, denom);
        result.simplify();
        return result;
    }

    Fraction operator*(const Fraction& other) const {
        int num = numerator * other.numerator;
        int denom = denominator * other.denominator;
        Fraction result(num, denom);
        result.simplify();
        return result;
    }

    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            cout << "Error: Division by zero is not allowed." << endl;
            return Fraction(0, 1);
        }
        int num = numerator * other.denominator;
        int denom = denominator * other.numerator;
        Fraction result(num, denom);
        result.simplify();
        return result;
    }

    friend ostream& operator<<(ostream& os, const Fraction& fraction) {
        os << fraction.numerator;
        if (fraction.denominator != 1) os << "/" << fraction.denominator;
        return os;
    }
};

int main() {
    int num1, denom1, num2, denom2;
    cout << "Enter the numerator and denominator for the first fraction: ";
    cin >> num1 >> denom1;
    Fraction f1(num1, denom1);

    cout << "Enter the numerator and denominator for the second fraction: ";
    cin >> num2 >> denom2;
    Fraction f2(num2, denom2);

    Fraction sum = f1 + f2;
    Fraction diff = f1 - f2;
    Fraction prod = f1 * f2;
    Fraction quot = f1 / f2;

    cout << "First fraction: " << f1 << endl;
    cout << "Second fraction: " << f2 << endl;
    cout << "Sum: " << sum << endl;
    cout << "Difference: " << diff << endl;
    cout << "Product: " << prod << endl;
    cout << "Quotient: " << quot << endl;

    return 0;
}

