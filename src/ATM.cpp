#include "ATM.h"
#include <fstream>
#include <iostream>
#include <iomanip>

ATM::ATM() {
    currentAccount = nullptr;
    loadAccounts();
}

ATM::~ATM() {
    saveAccounts();
    currentAccount = nullptr;
}

void ATM::loadAccounts() {
    db.loadAccounts(accounts);
}

void ATM::saveAccounts() {
    db.saveAccounts(accounts);
}

bool ATM::login(int accountNumber, int pin) {
    for (auto& acc : accounts) {
        if (acc.getAccountNumber() == accountNumber && acc.validatePin(pin)) {
            currentAccount = &acc;
            return true;
        }
    }
    return false;
}

bool ATM::createAccount(int accountNumber, int pin) {

    for (const auto& acc : accounts) {
        if (acc.getAccountNumber() == accountNumber) {
            return false;
        }
    }
  
    accounts.push_back(Account(accountNumber, 0.0, pin));
    saveAccounts();
    return true;
}

bool ATM::withdraw(double amount) {
    if (currentAccount) {
        if (currentAccount->withdraw(amount)) {
            saveAccounts();
            return true;
        }
    }
    return false;
}

void ATM::deposit(double amount) {
    if (currentAccount) {
        currentAccount->deposit(amount);
        saveAccounts();
    }
}

double ATM::checkBalance() {
    return currentAccount ? currentAccount->getBalance() : 0.0;
}

void ATM::logout() {
    currentAccount = nullptr;
}