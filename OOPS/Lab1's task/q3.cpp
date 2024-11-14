#include <iostream>

using namespace std;

class bankac {
private:
    string name;
    int ac;
    float balance;

public:
    // Method to set initial balance
    void setBalance(float initialBalance) {
        balance = initialBalance;
    }

    void updateBalance() {
        char check;
        float amount;
        int tran = 0;

        while(tran != -1) {
            cout << "Withdrawal or Deposit? (W/D): ";
            cin >> check;

            if(check == 'W' || check == 'w') {
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                if(balance < amount) {
                    cout << "Withdrawal failed" << endl << "Limit exceeded" << endl;
                } else {
                    balance -= amount;
                    cout << "Withdrawal successful" << endl << "Current balance: " << balance << endl;
                }
            } else if(check == 'D' || check == 'd') {
                cout << "Enter amount to deposit: ";
                cin >> amount;
                balance += amount;
                cout << "Deposit successful" << endl << "Current balance: " << balance << endl;
            } else {
                cout << "Invalid option. Please enter 'W' for withdrawal or 'D' for deposit." << endl;
            }

            cout << "To terminate transaction enter -1, to continue enter any other number: ";
            cin >> tran;
        }
    }
};

int main() {
    bankac person;
    person.setBalance(0.0f);

    person.updateBalance();
    return 0;
}
