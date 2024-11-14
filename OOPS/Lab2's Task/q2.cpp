#include <iostream>
using namespace std;

class ComplexNumber {
private:
    int real;
    int imaginary;

public:
    ComplexNumber(int r = 0, int i = 0) : real(r), imaginary(i) {}

    ComplexNumber add(const ComplexNumber& other) const {
        return ComplexNumber(real + other.real, imaginary + other.imaginary);
    }

    ComplexNumber subtract(const ComplexNumber& other) const {
        return ComplexNumber(real - other.real, imaginary - other.imaginary);
    }

    void display() const {
        cout << real << " + " << imaginary << "i" << endl;
    }
};

int main() {
    ComplexNumber num1(3, 4);
    ComplexNumber num2(1, 2);

    ComplexNumber sum = num1.add(num2);
    ComplexNumber diff = num1.subtract(num2);

    cout << "First complex number: ";
    num1.display();

    cout << "Second complex number: ";
    num2.display();

    cout << "Sum: ";
    sum.display();

    cout << "Difference: ";
    diff.display();

    return 0;
}

