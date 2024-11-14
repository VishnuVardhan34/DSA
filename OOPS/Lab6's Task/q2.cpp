//q2
#include <iostream>
#include <stdexcept>

class BankAccount {
private:
    double balance;

public:
    BankAccount() : balance(0.0) {}

    void deposit(double amount) {
        if (amount < 0) {
            throw std::invalid_argument("Deposit amount cannot be negative.");
        }
        balance += amount;
        std::cout << "Deposited: $" << amount << ", New Balance: $" << balance << std::endl;
    }

    void withdraw(double amount) {
        if (amount < 0) {
            throw std::invalid_argument("Withdrawal amount cannot be negative.");
        }
        if (amount > balance) {
            throw std::out_of_range("Insufficient balance for this withdrawal.");
        }
        balance -= amount;
        std::cout << "Withdrew: $" << amount << ", New Balance: $" << balance << std::endl;
    }

    double getBalance() const {
        return balance;
    }
};

int main() {
    BankAccount account;
    int choice;
    double amount;

    while (true) {
        std::cout << "\n1. Deposit\n2. Withdraw\n3. Check Balance\n4. Exit\nChoose an option: ";
        std::cin >> choice;

        try {
            switch (choice) {
                case 1:
                    std::cout << "Enter deposit amount: ";
                    std::cin >> amount;
                    account.deposit(amount);
                    break;

                case 2:
                    std::cout << "Enter withdrawal amount: ";
                    std::cin >> amount;
                    account.withdraw(amount);
                    break;

                case 3:
                    std::cout << "Current Balance: $" << account.getBalance() << std::endl;
                    break;

                case 4:
                    std::cout << "Exiting program." << std::endl;
                    return 0;

                default:
                    std::cout << "Invalid option. Please choose again." << std::endl;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}
