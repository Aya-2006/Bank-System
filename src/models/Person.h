#pragma once
#include <string>
#include "../utils/Validation.h"
using namespace std;


class Person {
protected:
    int id;
    string name;
    string password;

public:
    Person() : id(0), name(""), password("") {}

    Person(int id, const string& name, const string& password) : id(0) {
        setId(id);
        setName(name);
        setPassword(password);
    }

    virtual ~Person() = default;

    // Setters
    void setName(const string& newName) {
        if (Validation::validateName(newName)) name = newName;
        else cout << "Invalid name\n";
    }

    void setPassword(const string& newPassword) {
        if (Validation::validatePassword(newPassword)) password = newPassword;
        else cout << "Invalid password\n";
    }

    void setId(int newId) { id = newId; }

    // Getters
    const string& getName() const { return name; }
    const string& getPassword() const { return password; }
    int getId() const { return id; }

    
    virtual bool canManageClients() const { return false; }
    virtual bool canManageEmployees() const { return false; }
    virtual string getRoleName() const = 0;

    virtual void display() const {
        cout << "ID : " << id << "\n";
        cout << "Name : " << name << "\n";
    }
};
