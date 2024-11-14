#include <iostream>
#include <stdexcept>
#include <string>
#include <cctype>

using namespace std;

class BankAccount {
private:
    string accountNumber;
    double balance;

public:
    BankAccount(const string& accNum) : balance(0.0) {
        setAccountNumber(accNum);
    }

    void setAccountNumber(const string& accNum) {
        if (accNum.length() != 10 || !all_of(accNum.begin(), accNum.end(), ::isdigit)) {
            throw invalid_argument("Invalid account number format: must be 10 digits.");
        }
        accountNumber = accNum;
    }

    void deposit(double amount) {
        if (amount < 0) {
            throw invalid_argument("Deposit amount cannot be negative.");
        }
        balance += amount;
        cout << "Deposited: $" << amount << ", New Balance: $" << balance << endl;
    }

    void withdraw(double amount) {
        if (amount < 0) {
            throw invalid_argument("Withdrawal amount cannot be negative.");
        }
        if (amount > balance) {
            throw out_of_range("Insufficient balance for this withdrawal.");
        }
        balance -= amount;
        cout << "Withdrew: $" << amount << ", New Balance: $" << balance << endl;
    }

    double getBalance() const {
        return balance;
    }

    void displayAccountNumber() const {
        cout << "Account Number: " << accountNumber << endl;
    }
};

int main() {
    string accNum;
    double amount;
    int choice;

    cout << "Enter your 10-digit account number: ";
    cin >> accNum;

    try {
        BankAccount account(accNum);

        while (true) {
            cout << "\n1. Deposit\n2. Withdraw\n3. Check Balance\n4. Exit\nChoose an option: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Enter deposit amount: ";
                    cin >> amount;
                    account.deposit(amount);
                    break;

                case 2:
                    cout << "Enter withdrawal amount: ";
                    cin >> amount;
                    account.withdraw(amount);
                    break;

                case 3:
                    account.displayAccountNumber();
                    cout << "Current Balance: $" << account.getBalance() << endl;
                    break;

                case 4:
                    cout << "Exiting program." << endl;
                    return 0;

                default:
                    cout << "Invalid option. Please choose again." << endl;
            }
        }
    }
    catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }
    catch (const out_of_range& e) {
        cerr << "Error: " << e.what() << endl;
    }
    catch (...) {
        cerr << "An unknown error occurred." << endl;
    }

    return 0;
}
