#pragma once
#include "Person.h"
using namespace std;

class Employee : public Person {
private:
    double salary;

public:
    Employee() : Person(), salary(0) {}

    Employee(int id, const string& name, const string& password, double salary)
        : Person(id, name, password) {
        setSalary(salary);
    }

    void setSalary(double newSalary) {
        if (Validation::validateSalary(newSalary)) salary = newSalary;
        else cout << "Invalid salary\n";
    }

    double getSalary() const { return salary; }

    
    bool canManageClients() const override { return true; }

    string getRoleName() const override { return "Employee"; }

    void display() const override {
        Person::display();
        cout << "Salary : " << salary << "\n";
    }
};
