#pragma once
#include <vector>
#include <optional>
#include "../../models/Client.h"
using namespace std;


class IClientRepository {
public:
    virtual ~IClientRepository() = default;

    virtual int add(Client& client) = 0;
    virtual bool update(const Client& client) = 0;
    virtual optional<Client> findById(int id) = 0;
    virtual vector<Client> getAll() = 0;
};
