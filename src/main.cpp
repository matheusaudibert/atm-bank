#include "ATM.h"
#include <iostream>
#include <limits>
#include <iomanip>
#include <windows.h>
#include <string>

void clearScreen() {
    system("cls");
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

bool isNumeric(const std::string& str) {
    return !str.empty() && str.find_first_not_of("0123456789") == std::string::npos;
}

std::string getNumericInput(const std::string& prompt) {
    std::string input;
    while (true) {
        setColor(7);
        std::cout << prompt;
        std::cin >> input;
        
        if (isNumeric(input)) {
            return input;
        }
        
        setColor(12);
        std::cout << "Erro: Digite apenas números!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void showHeader() {
    setColor(14); //amarelo
    std::cout << "╔═══════════════════════════════════════╗\n";
    std::cout << "║            BANCO VIRTUAL              ║\n";
    std::cout << "╚═══════════════════════════════════════╝\n\n";
    setColor(7);
}

void showMainMenu() {
    setColor(11); //azulclaro
    std::cout << "╔══════════════ MENU PRINCIPAL ═════════════╗\n";
    std::cout << "║                                           ║\n";
    std::cout << "║   1. Acessar Conta                        ║\n";
    std::cout << "║   2. Criar Nova Conta                     ║\n";
    std::cout << "║   3. Sair                                 ║\n";
    std::cout << "║                                           ║\n";
    std::cout << "╚═══════════════════════════════════════════╝\n";
    setColor(7);
}

void showAccountMenu(double balance) {
    setColor(10); //verde
    std::cout << "╔═════════════ MENU DA CONTA ════════════╗\n";
    std::cout << "║                                        ║\n";
    std::cout << "║  Saldo Atual: R$ " << std::fixed << std::setprecision(2) << std::setw(14) << balance << "        ║\n";
    std::cout << "║                                        ║\n";
    std::cout << "║  1. Consultar Saldo                    ║\n";
    std::cout << "║  2. Realizar Depósito                  ║\n";
    std::cout << "║  3. Realizar Saque                     ║\n";
    std::cout << "║  4. Voltar ao Menu Principal           ║\n";
    std::cout << "║                                        ║\n";
    std::cout << "╚════════════════════════════════════════╝\n";
    setColor(7);
}

void showError(const std::string& message) {
    setColor(12); //vermelho
    std::cout << "ERRO: " << message << "\n";
    setColor(7);
}

void showSuccess(const std::string& message) {
    setColor(10); // verdee
    std::cout << "\nSUCESSO: " << message << "\n";
    setColor(7);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    ATM atm;
    int choice;
    double amount;

    while (true) {
        clearScreen();
        showHeader();
        showMainMenu();
        
        std::string choiceStr = getNumericInput("\nDigite sua escolha: ");
        choice = std::stoi(choiceStr);
        clearScreen();
        showHeader();

        if (choice == 3) {
            break;
        }

        switch(choice) {
            case 1: {
                std::string accNum = getNumericInput("Digite o número da conta: ");
                std::string pinStr = getNumericInput("Digite o PIN: ");
                
                int accountNumber = std::stoi(accNum);
                int pin = std::stoi(pinStr);

                if (atm.login(accountNumber, pin)) {
                    while (true) {
                        clearScreen();
                        showHeader();
                        showAccountMenu(atm.checkBalance());
                        
                        choiceStr = getNumericInput("\nDigite sua escolha: ");
                        choice = std::stoi(choiceStr);

                        if (choice == 4) break;

                        switch (choice) {
                            case 1:
                                std::cout << "\nSaldo atual: R$ " << std::fixed 
                                         << std::setprecision(2) << atm.checkBalance() << std::endl;
                                break;

                            case 2: {
                                std::string amountStr = getNumericInput("Valor para depósito: R$ ");
                                amount = std::stod(amountStr);
                                if (amount > 0) {
                                    atm.deposit(amount);
                                    showSuccess("Depósito realizado com sucesso!");
                                } else {
                                    showError("Valor inválido!");
                                }
                                break;
                            }

                            case 3: {
                                std::string amountStr = getNumericInput("Valor para saque: R$ ");
                                amount = std::stod(amountStr);
                                if (amount > 0) {
                                    if (atm.withdraw(amount)) {
                                        showSuccess("Saque realizado com sucesso!");
                                    } else {
                                        showError("Saldo insuficiente!");
                                    }
                                } else {
                                    showError("Valor inválido!");
                                }
                                break;
                            }

                            default:
                                showError("Opção inválida!");
                                break;
                        }
                        std::cout << "\nPressione ENTER para continuar...";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cin.get();
                    }
                } else {
                    showError("Conta ou PIN inválido!");
                    Sleep(2000);
                }
                break;
            }

            case 2: {
                std::string accNum = getNumericInput("Digite o número para nova conta: ");
                std::string pinStr = getNumericInput("Digite o PIN desejado: ");
                
                int accountNumber = std::stoi(accNum);
                int pin = std::stoi(pinStr);

                if (atm.createAccount(accountNumber, pin)) {
                    showSuccess("Conta criada com sucesso!");
                } else {
                    showError("Número de conta já existe!");
                }
                Sleep(2000);
                break;
            }

            default:
                showError("Opção inválida!");
                Sleep(2000);
                break;
        }
    }
    return 0;
}