#pragma once
#include "Person.h"
using namespace std;

class Client : public Person {
private:
    double balance;

public:
    Client() : Person(), balance(0) {}

    Client(int id, const string& name, const string& password, double balance)
        : Person(id, name, password) {
        setBalance(balance);
    }

    void setBalance(double newBalance) {
        if (Validation::validateBalance(newBalance)) balance = newBalance;
        else cout << "Invalid balance\n";
    }

    double getBalance() const { return balance; }

    
    void deposit(double amount) {
        if (amount > 0) balance += amount;
    }

    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }

    void checkBalance() const {
        cout << "Balance : " << balance << "\n";
    }

    string getRoleName() const override { return "Client"; }

    void display() const override {
        Person::display();
        cout << "Balance : " << balance << "\n";
    }
};
