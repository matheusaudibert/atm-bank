#include "Account.h"

Account::Account(int acc, double bal, int p) {
    accountNumber = acc;
    balance = bal;
    pin = p;
}

bool Account::validatePin(int p) const {
    return pin == p;
}

bool Account::withdraw(double amount) {
    if (amount <= balance) {
        balance -= amount;
        return true;
    }
    return false;
}

void Account::deposit(double amount) {
    balance += amount;
}

double Account::getBalance() const {
    return balance;
}

int Account::getAccountNumber() const {
    return accountNumber;
}