#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account {
private:
    int accountNumber;
    double balance;
    int pin;

public:
    Account(int acc, double bal, int p);
    bool validatePin(int p) const;
    bool withdraw(double amount);
    void deposit(double amount);
    double getBalance() const;
    int getAccountNumber() const;
    int getPin() const { return pin; } 
};

#endif