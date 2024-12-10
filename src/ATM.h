#ifndef ATM_H
#define ATM_H

#include "Account.h"
#include "Database.h"
#include <vector>
#include <string>

class ATM {
private:
    std::vector<Account> accounts;
    Account* currentAccount;
    Database db;

public:
    ATM();
    bool login(int accountNumber, int pin);
    bool createAccount(int accountNumber, int pin);
    bool withdraw(double amount);
    void deposit(double amount);
    double checkBalance();
    void loadAccounts();
    void saveAccounts();
    void logout();
    ~ATM();
};

#endif