#pragma once
#include "../repositories/interfaces/IClientRepository.h"
#include "../repositories/interfaces/IEmployeeRepository.h"
#include "../repositories/interfaces/IAdminRepository.h"
using namespace std;

class AuthService
{
private:
    IClientRepository &clientRepo;
    IEmployeeRepository &employeeRepo;
    IAdminRepository &adminRepo;

public:
    AuthService(IClientRepository &clientRepo, IEmployeeRepository &employeeRepo, IAdminRepository &adminRepo)
        : clientRepo(clientRepo), employeeRepo(employeeRepo), adminRepo(adminRepo) {}

    optional<Client> loginClient(int id, const string &password)
    {
        auto client = clientRepo.findById(id);
        if (client && client->getPassword() == password)
            return client;
        return nullopt;
    }

    optional<Employee> loginEmployee(int id, const string &password)
    {
        auto employee = employeeRepo.findById(id);
        if (employee && employee->getPassword() == password)
            return employee;
        return nullopt;
    }

    optional<Admin> loginAdmin(int id, const string &password)
    {
        auto admin = adminRepo.findById(id);
        if (admin && admin->getPassword() == password)
            return admin;
        return nullopt;
    }
};
