#pragma once
#include "../repositories/interfaces/IEmployeeRepository.h"
#include "../models/Person.h"
#include <stdexcept>
using namespace std;


class EmployeeManagementService {
private:
    IEmployeeRepository& employeeRepo;

    static void requirePermission(const Person& actingUser) {
        if (!actingUser.canManageEmployees()) {
            throw runtime_error(
                "Access denied: only an Admin can manage employees (current role: "
                + actingUser.getRoleName() + ")");
        }
    }

public:
    explicit EmployeeManagementService(IEmployeeRepository& employeeRepo) : employeeRepo(employeeRepo) {}

    int addEmployee(const Person& actingUser, Employee& employee) {
        requirePermission(actingUser);
        return employeeRepo.add(employee);
    }

    optional<Employee> searchEmployee(const Person& actingUser, int employeeId) {
        requirePermission(actingUser);
        return employeeRepo.findById(employeeId);
    }

    vector<Employee> listEmployees(const Person& actingUser) {
        requirePermission(actingUser);
        return employeeRepo.getAll();
    }

    bool editEmployee(const Person& actingUser, int employeeId,
                       const string& name, const string& password, double salary) {
        requirePermission(actingUser);
        auto employee = employeeRepo.findById(employeeId);
        if (!employee) return false;

        employee->setName(name);
        employee->setPassword(password);
        employee->setSalary(salary);
        return employeeRepo.update(*employee);
    }
};
