#pragma once
#include "../services/BankingService.h"
#include "../repositories/interfaces/IClientRepository.h"
#include "../utils/Console.h"
#include "../utils/Validation.h"
#include <iostream>
using namespace std;


class ClientManager {
public:
   
    static void run(int clientId, IClientRepository& clientRepo, BankingService& bankingService) {
        bool running = true;
        while (running) {
            Console::clearScreen();
            cout << "(1) Display my info\n"
                      << "(2) Check balance\n"
                      << "(3) Update Password\n"
                      << "(4) Withdraw\n"
                      << "(5) Deposit\n"
                      << "(6) Transfer amount\n"
                      << "(7) Logout\n\n"
                      << "Your choice is: ";
            int choice;
            if (!(cin >> choice)) { Console::clearInputBuffer(); continue; }

            try {
                switch (choice) {
                    case 1: {
                        auto client = clientRepo.findById(clientId);
                        if (client) client->display();
                        break;
                    }
                    case 2: {
                        auto client = clientRepo.findById(clientId);
                        if (client) client->checkBalance();
                        break;
                    }
                    case 3: {
                        string newPassword = Validation::enterPassword();
                        auto client = clientRepo.findById(clientId);
                        if (client) {
                            client->setPassword(newPassword);
                            clientRepo.update(*client);
                            cout << "Password updated.\n";
                        }
                        break;
                    }
                    case 4: {
                        double amount;
                        cout << "Enter amount to withdraw: ";
                        cin >> amount;
                        double newBalance = bankingService.withdraw(clientId, amount);
                        cout << "Withdrawn. New balance: " << newBalance << "\n";
                        break;
                    }
                    case 5: {
                        double amount;
                        cout << "Enter amount to deposit: ";
                        cin >> amount;
                        double newBalance = bankingService.deposit(clientId, amount);
                        cout << "Deposited. New balance: " << newBalance << "\n";
                        break;
                    }
                    case 6: {
                        int recipientId;
                        double amount;
                        cout << "Enter id of the recipient: ";
                        cin >> recipientId;
                        cout << "Enter amount to transfer: ";
                        cin >> amount;
                        bankingService.transfer(clientId, recipientId, amount);
                        cout << "Transfer completed.\n";
                        break;
                    }
                    case 7:
                        running = false;
                        break;
                    default:
                        cout << "Invalid choice\n";
                }
            } catch (const exception& e) {
                cout << "Error: " << e.what() << "\n";
            }

            if (running) Console::pause();
        }
    }
};
