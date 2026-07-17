#pragma once
#include "../services/ClientManagementService.h"
#include "../services/EmployeeManagementService.h"
#include "../repositories/interfaces/IAdminRepository.h"
#include "../models/Employee.h"
#include "../utils/Console.h"
#include "../utils/Validation.h"
#include <iostream>
using namespace std;

class AdminManager {
public:
    static void run(int adminId, IAdminRepository& adminRepo,
                     ClientManagementService& clientMgmtService,
                     EmployeeManagementService& employeeMgmtService) {
        bool running = true;
        while (running) {
            Console::clearScreen();
            cout << "(1) Display my info\n"
                      << "(2) Update Password\n"
                      << "(3) Add new client\n"
                      << "(4) Search for client\n"
                      << "(5) List all clients\n"
                      << "(6) Edit client info\n"
                      << "(7) Add new Employee\n"
                      << "(8) Search for Employee\n"
                      << "(9) List all Employees\n"
                      << "(10) Edit Employee info\n"
                      << "(11) Logout\n\n"
                      << "Your choice is: ";
            int choice;
            if (!(cin >> choice)) { Console::clearInputBuffer(); continue; }

            auto self = adminRepo.findById(adminId);
            if (!self) { cout << "Session error.\n"; break; }

            try {
                switch (choice) {
                    case 1:
                        self->display();
                        break;
                    case 2: {
                        string newPassword = Validation::enterPassword();
                        self->setPassword(newPassword);
                        adminRepo.update(*self); 
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
                    case 7: {
                        string name = Validation::enterName();
                        string password = Validation::enterPassword();
                        double salary = Validation::enterSalary();
                        Employee newEmployee(0, name, password, salary);
                        int id = employeeMgmtService.addEmployee(*self, newEmployee);
                        cout << "Employee added successfully. ID: " << id << "\n";
                        break;
                    }
                    case 8: {
                        int id;
                        cout << "Enter employee id: ";
                        cin >> id;
                        auto employee = employeeMgmtService.searchEmployee(*self, id);
                        if (employee) employee->display();
                        else cout << "Employee not found.\n";
                        break;
                    }
                    case 9: {
                        auto employees = employeeMgmtService.listEmployees(*self);
                        for (const auto& e : employees) {
                            e.display();
                            cout << "--------------------\n";
                        }
                        break;
                    }
                    case 10: {
                        int id;
                        cout << "Enter employee id: ";
                        cin >> id;
                        string name = Validation::enterName();
                        string password = Validation::enterPassword();
                        double salary = Validation::enterSalary();
                        bool ok = employeeMgmtService.editEmployee(*self, id, name, password, salary);
                        cout << (ok ? "Employee info updated.\n" : "Employee not found.\n");
                        break;
                    }
                    case 11:
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


