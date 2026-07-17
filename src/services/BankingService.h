#pragma once
#include "../repositories/interfaces/IClientRepository.h"
#include "../repositories/interfaces/ITransactionManager.h"
#include <stdexcept>
using namespace std;


class BankingService {
private:
    IClientRepository& clientRepo;
    ITransactionManager& txManager;

public:
    BankingService(IClientRepository& clientRepo, ITransactionManager& txManager)
        : clientRepo(clientRepo), txManager(txManager) {}

    double deposit(int clientId, double amount) {
        auto client = clientRepo.findById(clientId);
        if (!client) throw runtime_error("Client not found");
        if (amount <= 0) throw runtime_error("Deposit amount must be positive");

        client->deposit(amount);
        clientRepo.update(*client);
        return client->getBalance();
    }

    double withdraw(int clientId, double amount) {
        auto client = clientRepo.findById(clientId);
        if (!client) throw runtime_error("Client not found");
        if (amount <= 0) throw runtime_error("Withdraw amount must be positive");
        if (!client->withdraw(amount)) throw runtime_error("Insufficient balance");

        clientRepo.update(*client);
        return client->getBalance();
    }

    void transfer(int fromClientId, int toClientId, double amount) {
        if (fromClientId == toClientId) throw runtime_error("Cannot transfer to the same account");

        auto sender = clientRepo.findById(fromClientId);
        if (!sender) throw runtime_error("Sender not found");
        auto recipient = clientRepo.findById(toClientId);
        if (!recipient) throw runtime_error("Recipient not found");

        if (amount <= 0) throw runtime_error("Transfer amount must be positive");
        if (!sender->withdraw(amount)) throw runtime_error("Insufficient balance");
        recipient->deposit(amount);

        txManager.begin();
        try {
            clientRepo.update(*sender);
            clientRepo.update(*recipient);
            txManager.commit();
        } catch (...) {
            txManager.rollback();
            throw;
        }
    }

    double checkBalance(int clientId) {
        auto client = clientRepo.findById(clientId);
        if (!client) throw runtime_error("Client not found");
        return client->getBalance();
    }
};
