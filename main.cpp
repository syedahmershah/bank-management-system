#include <iostream>
#include <string>
#include <vector>
#include <limits>

int getInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid number.\n";
    }
}

float getFloat(const std::string& prompt) {
    float value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid amount.\n";
    }
}

std::string getLine(const std::string& prompt) {
    std::string line;
    std::cout << prompt;
    std::getline(std::cin, line);
    return line;
}

class Account {
public:
    int accountNumber;
    int pin;
    std::string name;
    float balance;

    Account(int accountNumber, int pin, const std::string& name, float balance)
        : accountNumber(accountNumber), pin(pin), name(name), balance(balance) {}
};

class ATM {
private:
    std::vector<Account> accounts;
    const int maxAccounts = 100;
    const int baseAccountNumber = 1001;

public:
    void createAccount() {
        if (accounts.size() >= maxAccounts) {
            std::cout << "Cannot create more accounts. Maximum limit reached.\n";
            return;
        }
        std::string name = getLine("Enter your name: ");
        
        int pin;
        while (true) {
            pin = getInt("Set your 4-digit PIN: ");
            if (pin >= 1000 && pin <= 9999)
                break;
            std::cout << "PIN must be a 4-digit number. Try again.\n";
        }
        
        float deposit = getFloat("Enter initial deposit amount: ");
        while (deposit < 0) {
            std::cout << "Deposit must be non-negative. Try again.\n";
            deposit = getFloat("Enter initial deposit amount: ");
        }
        
        int accountNumber = baseAccountNumber + accounts.size();
        accounts.emplace_back(accountNumber, pin, name, deposit);
        std::cout << "Account created successfully! Your account number is: " 
                  << accountNumber << "\n";
    }

    int login() {
        int accNo = getInt("Enter your account number: ");
        int pin = getInt("Enter your PIN: ");
        for (size_t i = 0; i < accounts.size(); ++i) {
            if (accounts[i].accountNumber == accNo && accounts[i].pin == pin) {
                std::cout << "Login successful! Welcome, " << accounts[i].name << ".\n";
                return static_cast<int>(i);
            }
        }
        std::cout << "Invalid account number or PIN.\n";
        return -1;
    }

    void deposit(int index) {
        float amount = getFloat("Enter amount to deposit: ");
        if (amount <= 0) {
            std::cout << "Invalid deposit amount.\n";
            return;
        }
        accounts[index].balance += amount;
        std::cout << "Deposit successful. New balance: " << accounts[index].balance << "\n";
    }

    void withdraw(int index) {
        float amount = getFloat("Enter amount to withdraw: ");
        if (amount <= 0) {
            std::cout << "Invalid withdrawal amount.\n";
            return;
        }
        if (amount > accounts[index].balance) {
            std::cout << "Insufficient funds.\n";
            return;
        }
        accounts[index].balance -= amount;
        std::cout << "Withdrawal successful. New balance: " << accounts[index].balance << "\n";
    }

    void checkBalance(int index) {
        std::cout << "Current balance: " << accounts[index].balance << "\n";
    }

    void run() {
        int choice;
        do {
            std::cout << "\n---------------------------------\n"
                      << "      Welcome to the ATM System\n"
                      << "---------------------------------\n"
                      << "1. Create New Account\n"
                      << "2. Login to Existing Account\n"
                      << "3. Exit\n";
            choice = getInt("Enter your choice: ");

            switch (choice) {
                case 1:
                    createAccount();
                    break;
                case 2: {
                    int index = login();
                    if (index != -1) {
                        int atmChoice;
                        do {
                            std::cout << "\n---------- ATM Menu ----------\n"
                                      << "1. Deposit\n"
                                      << "2. Withdraw\n"
                                      << "3. Check Balance\n"
                                      << "4. Logout\n";
                            atmChoice = getInt("Enter your choice: ");
                            switch (atmChoice) {
                                case 1:
                                    deposit(index);
                                    break;
                                case 2:
                                    withdraw(index);
                                    break;
                                case 3:
                                    checkBalance(index);
                                    break;
                                case 4:
                                    std::cout << "Logging out...\n";
                                    break;
                                default:
                                    std::cout << "Invalid choice. Please try again.\n";
                                    break;
                            }
                        } while (atmChoice != 4);
                    }
                    break;
                }
                case 3:
                    std::cout << "Thank you for using the ATM System. Goodbye!\n";
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    break;
            }
        } while (choice != 3);
    }
};

int main() {
    ATM atm;
    atm.run();
    return 0;
}
