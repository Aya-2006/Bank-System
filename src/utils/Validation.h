#pragma once
#include <iostream>
#include <string>
using namespace std;


class Validation {
public:
    static bool validateName(const string& name) {
        if (!(name.size() >= 2 && name.size() <= 20)) {
            cout << "the size of name must be >=2 and <=20\n";
            return false;
        }
        for (char c : name) {
            if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
                cout << "name must contain alphabetic characters only\n";
                return false;
            }
        }
        return true;
    }

    static bool validatePassword(const string& password) {
        if (password.size() >= 8 && password.size() <= 20) return true;
        cout << "the password must be >= 8 And <= 20\n";
        return false;
    }

    static bool validateBalance(double balance) {
        if (balance < 1500) {
            cout << "balance must be >= 1500\n";
            return false;
        }
        return true;
    }

    static bool validateSalary(double salary) {
        if (salary < 5000) {
            cout << "salary must be >= 5000\n";
            return false;
        }
        return true;
    }

    
    static string enterName() {
        string name;
        cout << "Enter name: ";
        cin >> name;
        while (!validateName(name)) {
            cout << "Enter name: ";
            cin >> name;
        }
        return name;
    }

    static string enterPassword() {
        string password;
        cout << "Enter password: ";
        cin >> password;
        while (!validatePassword(password)) {
            cout << "Enter password: ";
            cin >> password;
        }
        return password;
    }

    static double enterBalance() {
        double balance;
        cout << "Enter balance: ";
        cin >> balance;
        while (!validateBalance(balance)) {
            cout << "Enter balance: ";
            cin >> balance;
        }
        return balance;
    }

    static double enterSalary() {
        double salary;
        cout << "Enter salary: ";
        cin >> salary;
        while (!validateSalary(salary)) {
            cout << "Enter salary: ";
            cin >> salary;
        }
        return salary;
    }
};
