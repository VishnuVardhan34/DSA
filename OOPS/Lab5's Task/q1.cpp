#include <iostream>
#include <cmath>

using namespace std;

class Polynomial {
private:
    int degree;
    int coefficients[100];

public:
    Polynomial(int deg = 0) : degree(deg) {
        for (int i = 0; i <= degree; ++i) {
            coefficients[i] = 0;
        }
    }

    void setCoefficient(int power, int coeff) {
        if (power > degree) {
            cout << "Power exceeds polynomial degree." << endl;
            return;
        }
        coefficients[power] = coeff;
    }

    Polynomial operator+(const Polynomial& other) const {
        int maxDegree = max(degree, other.degree);
        Polynomial result(maxDegree);

        for (int i = 0; i <= maxDegree; ++i) {
            int a = (i <= degree) ? coefficients[i] : 0;
            int b = (i <= other.degree) ? other.coefficients[i] : 0;
            result.coefficients[i] = a + b;
        }
        return result;
    }

    Polynomial operator-(const Polynomial& other) const {
        int maxDegree = max(degree, other.degree);
        Polynomial result(maxDegree);

        for (int i = 0; i <= maxDegree; ++i) {
            int a = (i <= degree) ? coefficients[i] : 0;
            int b = (i <= other.degree) ? other.coefficients[i] : 0;
            result.coefficients[i] = a - b;
        }
        return result;
    }

    Polynomial operator*(const Polynomial& other) const {
        int resultDegree = degree + other.degree;
        Polynomial result(resultDegree);

        for (int i = 0; i <= degree; ++i) {
            for (int j = 0; j <= other.degree; ++j) {
                result.coefficients[i + j] += coefficients[i] * other.coefficients[j];
            }
        }
        return result;
    }

    friend ostream& operator<<(ostream& os, const Polynomial& poly) {
        bool isFirstTerm = true;
        for (int i = poly.degree; i >= 0; --i) {
            if (poly.coefficients[i] == 0) continue;

            if (!isFirstTerm && poly.coefficients[i] > 0) {
                os << " + ";
            } else if (poly.coefficients[i] < 0) {
                os << " - ";
            }

            if (abs(poly.coefficients[i]) != 1 || i == 0) {
                os << abs(poly.coefficients[i]);
            }
            if (i > 0) os << "x";
            if (i > 1) os << "^" << i;
            isFirstTerm = false;
        }

        if (isFirstTerm) os << "0";  // For zero polynomial
        return os;
    }
};

int main() {
    int degree1, degree2;

    cout << "Enter the degree of the first polynomial: ";
    cin >> degree1;
    Polynomial p1(degree1);

    cout << "Enter the coefficients for the first polynomial (from constant term to highest degree):\n";
    for (int i = 0; i <= degree1; ++i) {
        int coeff;
        cout << "Coefficient for x^" << i << ": ";
        cin >> coeff;
        p1.setCoefficient(i, coeff);
    }

    cout << "Enter the degree of the second polynomial: ";
    cin >> degree2;
    Polynomial p2(degree2);

    cout << "Enter the coefficients for the second polynomial (from constant term to highest degree):\n";
    for (int i = 0; i <= degree2; ++i) {
        int coeff;
        cout << "Coefficient for x^" << i << ": ";
        cin >> coeff;
        p2.setCoefficient(i, coeff);
    }

    Polynomial sum = p1 + p2;
    Polynomial diff = p1 - p2;
    Polynomial prod = p1 * p2;

    cout << "\nPolynomial p1: " << p1 << endl;
    cout << "Polynomial p2: " << p2 << endl;
    cout << "Sum (p1 + p2): " << sum << endl;
    cout << "Difference (p1 - p2): " << diff << endl;
    cout << "Product (p1 * p2): " << prod << endl;

    return 0;
}

