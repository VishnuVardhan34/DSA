#include <iostream>
#include <iomanip>
using namespace std;

class Currency {
private:
    double usd;
    static constexpr double exchangeRate = 0.85; // Exchange rate for USD to EUR

public:
    Currency(double amountUSD = 0.0) : usd(amountUSD) {}

    double getUSD() const { return usd; }
    double getEUR() const { return usd * exchangeRate; }

    Currency operator+(const Currency& other) const {
        return Currency(usd + other.usd);
    }

    Currency operator-(const Currency& other) const {
        return Currency(usd - other.usd);
    }

    Currency operator*(double multiplier) const {
        return Currency(usd * multiplier);
    }

    Currency operator/(double divisor) const {
        if (divisor == 0) {
            throw invalid_argument("Division by zero is not allowed.");
        }
        return Currency(usd / divisor);
    }

    friend ostream& operator<<(ostream& os, const Currency& currency) {
        os << fixed << setprecision(2)
           << currency.usd << " USD | " << currency.getEUR() << " EUR";
        return os;
    }
};

int main() {
    double amount1, amount2;
    cout << "Enter amount in USD for the first currency: ";
    cin >> amount1;
    Currency c1(amount1);
    cout << "Enter amount in USD for the second currency: ";
    cin >> amount2;
    Currency c2(amount2);

    Currency sum = c1 + c2;
    Currency diff = c1 - c2;
    Currency product = c1 * 1.5; // example multiplier
    Currency quotient = c1 / 2.0; // example divisor

    cout << "First currency: " << c1 << endl;
    cout << "Second currency: " << c2 << endl;
    cout << "Sum: " << sum << endl;
    cout << "Difference: " << diff << endl;
    cout << "Product (c1 * 1.5): " << product << endl;
    cout << "Quotient (c1 / 2.0): " << quotient << endl;

    return 0;
}

