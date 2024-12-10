#ifndef DATABASE_H
#define DATABASE_H

#include "Account.h"
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <filesystem>

class Database {
private:
    std::string filename;

    void createDataDirectory() {
        std::filesystem::create_directories("data");
    }

public:
    Database(const std::string& file = "data/accounts.txt") : filename(file) {
        createDataDirectory();
    }
    
    bool loadAccounts(std::vector<Account>& accounts) {
        std::ifstream file(filename);
        accounts.clear();
        
        if (!file.is_open()) {
            return true;
        }
        
        int accountNumber, pin;
        double balance;
        
        while (file >> accountNumber >> balance >> pin) {
            accounts.push_back(Account(accountNumber, balance, pin));
        }
        
        file.close();
        return true;
    }
    
    bool saveAccounts(const std::vector<Account>& accounts) {
        createDataDirectory();
        std::ofstream file(filename, std::ios::trunc);
        
        if (!file.is_open()) {
            return false;
        }
        
        for (const auto& acc : accounts) {
            file << acc.getAccountNumber() << " "
                 << std::fixed << std::setprecision(2) << acc.getBalance() << " "
                 << acc.getPin() << "\n";
        }
        
        file.close();
        return true;
    }

    virtual ~Database() {}
};

#endif