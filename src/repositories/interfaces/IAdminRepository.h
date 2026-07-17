#pragma once
#include <vector>
#include <optional>
#include "../../models/Admin.h"
using namespace std;

class IAdminRepository {
public:
    virtual ~IAdminRepository() = default;

    virtual int add(Admin& admin) = 0;
    virtual bool update(const Admin& admin) = 0;
    virtual optional<Admin> findById(int id) = 0;
    virtual vector<Admin> getAll() = 0;
};
