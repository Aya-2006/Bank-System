#pragma once
#include "../services/ClientManagementService.h"
#include "../repositories/interfaces/IEmployeeRepository.h"
#include "../models/Employee.h"
#include "../utils/Console.h"
#include "../utils/Validation.h"
#include <iostream>
using namespace std;

class EmployeeManager {
public:
    static void run(int employeeId, IEmployeeRepository& employeeRepo,
                     ClientManagementService& clientMgmtService) {
        bool running = true;
        while (running) {
            Console::clearScreen();
            cout << "(1) Display my info\n"
                      << "(2) Update Password\n"
                      << "(3) Add new client\n"
                      << "(4) Search for client\n"
                      << "(5) List all clients\n"
                      << "(6) Edit client info\n"
                      << "(7) Logout\n\n"
                      << "Your choice is: ";
            int choice;
            if (!(cin >> choice)) { Console::clearInputBuffer(); continue; }

            auto self = employeeRepo.findById(employeeId);
            if (!self) { cout << "Session error.\n"; break; }

            try {
                switch (choice) {
                    case 1:
                        self->display();
                        break;
                    case 2: {
                        string newPassword = Validation::enterPassword();
                        self->setPassword(newPassword);
                        employeeRepo.update(*self);
                        cout << "Password updated.\n";
                        break;
                    }
                    case 3: {
                        string name = Validation::enterName();
                        string password = Validation::enterPassword();
                        double balance = Validation::enterBalance();
                        Client newClient(0, name, password, balance);
                        int id = clientMgmtService.addClient(*self, newClient);
                        cout << "Client added successfully. ID: " << id << "\n";
                        break;
                    }
                    case 4: {
                        int id;
                        cout << "Enter client id: ";
                        cin >> id;
                        auto client = clientMgmtService.searchClient(*self, id);
                        if (client) client->display();
                        else cout << "Client not found.\n";
                        break;
                    }
                    case 5: {
                        auto clients = clientMgmtService.listClients(*self);
                        for (const auto& c : clients) {
                            c.display();
                            cout << "-------------------------\n";
                        }
                        break;
                    }
                    case 6: {
                        int id;
                        cout << "Enter client id: ";
                        cin >> id;
                        string name = Validation::enterName();
                        string password = Validation::enterPassword();
                        double balance = Validation::enterBalance();
                        bool ok = clientMgmtService.editClient(*self, id, name, password, balance);
                        cout << (ok ? "Client info updated.\n" : "Client not found.\n");
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
