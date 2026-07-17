#pragma once
#include "Employee.h"
using namespace std;

class Admin : public Employee {
public:
    Admin() : Employee() {}

    Admin(int id, const string& name, const string& password, double salary)
        : Employee(id, name, password, salary) {}

    bool canManageEmployees() const override { return true; }

    string getRoleName() const override { return "Admin"; }
};
