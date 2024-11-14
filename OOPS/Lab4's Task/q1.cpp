#include <iostream>
using namespace std;

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    Complex add(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex subtract(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex multiply(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag,
                       real * other.imag + imag * other.real);
    }

    Complex divide(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        if (denominator == 0) {
            cout << "Division by zero is not allowed." << endl;
            return Complex();
        }
        double realPart = (real * other.real + imag * other.imag) / denominator;
        double imagPart = (imag * other.real - real * other.imag) / denominator;
        return Complex(realPart, imagPart);
    }

    void display() const {
        cout << real;
        if (imag >= 0) cout << " + " << imag << "i";
        else cout << " - " << -imag << "i";
    }
};

int main() {
    double r1, i1, r2, i2;
    cout << "Enter the real and imaginary parts of the first complex number: ";
    cin >> r1 >> i1;
    Complex c1(r1, i1);

    cout << "Enter the real and imaginary parts of the second complex number: ";
    cin >> r2 >> i2;
    Complex c2(r2, i2);

    Complex sum = c1.add(c2);
    Complex diff = c1.subtract(c2);
    Complex prod = c1.multiply(c2);
    Complex quot = c1.divide(c2);

    cout << "First complex number: ";
    c1.display();
    cout << endl;

    cout << "Second complex number: ";
    c2.display();
    cout << endl;

    cout << "Sum: ";
    sum.display();
    cout << endl;

    cout << "Difference: ";
    diff.display();
    cout << endl;

    cout << "Product: ";
    prod.display();
    cout << endl;

    cout << "Quotient: ";
    quot.display();
    cout << endl;

    return 0;
}
