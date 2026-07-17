#pragma once
#include <iostream>
#include "../services/AuthService.h"
#include "../services/BankingService.h"
#include "../services/ClientManagementService.h"
#include "../services/EmployeeManagementService.h"
#include "../repositories/interfaces/IAdminRepository.h"
#include "../repositories/interfaces/IEmployeeRepository.h"
#include "../models/Admin.h"
#include "ClientManager.h"
#include "EmployeeManager.h"
#include "AdminManager.h"
#include "../utils/Console.h"
#include "../utils/Validation.h"
using namespace std;

class Screens
{
private:
    static void bankName()
    {
        cout << "======================================\n";
        cout << "         B A N K   S Y S T E M\n";
        cout << "======================================\n";
    }

    static void welcome()
    {
        Console::clearScreen();
        bankName();
        Console::sleepMs(800);
    }

    static int loginAs()
    {
        while (true)
        {
            cout << "\n(1) Admin\n(2) Employee\n(3) Client\n(0) Exit\n\nLogin as: ";
            int choice;
            if (!(cin >> choice))
            {
                if (cin.eof())
                    return 0;
                Console::clearInputBuffer();
                continue;
            }
            if (choice == 0 || choice == 1 || choice == 2 || choice == 3)
                return choice;
            cout << "Invalid choice.\n";
        }
    }

    static void bootstrapFirstAdminIfNeeded(IAdminRepository &adminRepo)
    {
        auto admins = adminRepo.getAll();
        if (!admins.empty())
            return;

        Console::clearScreen();
        cout << "No admin account exists yet. Let's create the first Admin.\n";
        string name = Validation::enterName();
        string password = Validation::enterPassword();
        double salary = Validation::enterSalary();

        Admin admin(0, name, password, salary);
        int id = adminRepo.add(admin);
        cout << "Admin created with ID: " << id << ". Please remember it to login.\n";
        Console::pause();
    }

public:
    static void runApp(AuthService &authService,
                       BankingService &bankingService,
                       ClientManagementService &clientMgmtService,
                       EmployeeManagementService &employeeMgmtService,
                       IClientRepository &clientRepo,
                       IEmployeeRepository &employeeRepo,
                       IAdminRepository &adminRepo)
    {
        welcome();
        bootstrapFirstAdminIfNeeded(adminRepo);

        while (true)
        {
            Console::clearScreen();
            int role = loginAs();
            if (role == 0)
            {
                cout << "Goodbye!\n";
                break;
            }

            int id;
            string password;
            cout << "Enter id: ";
            cin >> id;
            cout << "Enter password: ";
            cin >> password;

            if (role == 1)
            {
                auto admin = authService.loginAdmin(id, password);
                if (!admin)
                {
                    cout << "Incorrect id or password.\n";
                    Console::pause();
                    continue;
                }
                AdminManager::run(admin->getId(), adminRepo, clientMgmtService, employeeMgmtService);
            }
            else if (role == 2)
            {
                auto employee = authService.loginEmployee(id, password);
                if (!employee)
                {
                    cout << "Incorrect id or password.\n";
                    Console::pause();
                    continue;
                }
                EmployeeManager::run(employee->getId(), employeeRepo, clientMgmtService);
            }
            else
            {
                auto client = authService.loginClient(id, password);
                if (!client)
                {
                    cout << "Incorrect id or password.\n";
                    Console::pause();
                    continue;
                }
                ClientManager::run(client->getId(), clientRepo, bankingService);
            }
        }
    }
};
