#pragma once
#include <vector>
#include <optional>
#include "../../models/Employee.h"
using namespace std;

class IEmployeeRepository {
public:
    virtual ~IEmployeeRepository() = default;

    virtual int add(Employee& employee) = 0;
    virtual bool update(const Employee& employee) = 0;
    virtual optional<Employee> findById(int id) = 0;
    virtual vector<Employee> getAll() = 0;
};
