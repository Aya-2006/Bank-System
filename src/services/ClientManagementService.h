#pragma once
#include "../repositories/interfaces/IClientRepository.h"
#include "../models/Person.h"
#include <stdexcept>
using namespace std;

class ClientManagementService
{
private:
    IClientRepository &clientRepo;

    static void requirePermission(const Person &actingUser)
    {
        if (!actingUser.canManageClients())
        {
            throw runtime_error(
                "Access denied: only an Employee/Admin can manage clients (current role: " + actingUser.getRoleName() + ")");
        }
    }

public:
    explicit ClientManagementService(IClientRepository &clientRepo) : clientRepo(clientRepo) {}

    int addClient(const Person &actingUser, Client &client)
    {
        requirePermission(actingUser);
        return clientRepo.add(client);
    }

    optional<Client> searchClient(const Person &actingUser, int clientId)
    {
        requirePermission(actingUser);
        return clientRepo.findById(clientId);
    }

    vector<Client> listClients(const Person &actingUser)
    {
        requirePermission(actingUser);
        return clientRepo.getAll();
    }

    bool editClient(const Person &actingUser, int clientId,
                    const string &name, const string &password, double balance)
    {
        requirePermission(actingUser);
        auto client = clientRepo.findById(clientId);
        if (!client)
            return false;

        client->setName(name);
        client->setPassword(password);
        client->setBalance(balance);
        return clientRepo.update(*client);
    }
};
