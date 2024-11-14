#include <iostream>
using namespace std;

class BankAccount {
private:
    int accountNumber;
    string accountHolderName;
    int balance;

public:
    BankAccount(int accNumber, string holderName, int initialBalance) {
        accountNumber = accNumber;
        accountHolderName = holderName;
        balance = initialBalance;
    }

    void deposit(int amount) {
        balance += amount;
        cout << "Deposited: " << amount << endl;
    }

    void withdraw(int amount) {
        if (amount > balance) {
            cout << "Insufficient funds!" << endl;
        } else {
            balance -= amount;
            cout << "Withdrawn: " << amount << endl;
        }
    }

    void displayAccountDetails() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance: " << balance << endl;
    }
};

int main() {
    BankAccount account(12345, "John Doe", 1000);

    cout << "Account created!" << endl;
    account.displayAccountDetails();

    account.deposit(500);
    account.withdraw(200);

    cout << "\nUpdated account details:" << endl;
    account.displayAccountDetails();

    return 0;
}

