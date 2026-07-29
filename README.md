# Bank System

#### Video Demo: https://youtu.be/vAYMLQodY7M

## Description

Bank System is a command-line banking application developed in C++ with PostgreSQL as the database management system. This project was created as my final project for Harvard University's CS50x course. The main goal of the project is to simulate a real banking system by providing different roles and banking services while following modern software engineering practices.

The application supports three different user roles: Administrator, Employee, and Client. Each role has its own permissions and responsibilities. This separation makes the application more realistic and demonstrates role-based access control.

Clients can perform banking operations such as depositing money, withdrawing money, transferring money to another account, and checking their account information. Employees are responsible for managing clients by creating new accounts, updating client information, and searching for existing clients. Administrators have all employee permissions in addition to employee management features.

One of the main objectives of this project was not only to build a functional banking application but also to apply software engineering concepts learned during my programming journey. Therefore, I focused on writing clean, maintainable, and extensible code.

## Technologies Used

- C++
- PostgreSQL
- CMake
- Git & GitHub

## Project Structure

The project is divided into several folders to keep the code organized.

### Models

The Models folder contains the classes representing the application's entities such as Person, Client, Employee, and Admin.

### Repositories

The Repository layer is responsible for communicating directly with the PostgreSQL database. It separates database operations from business logic, making the application easier to maintain.

### Services

The Services layer contains the business logic of the application. It performs validation, handles banking operations, and coordinates communication between the user interface and the database.

### UI

The UI folder contains the command-line interface that allows users to interact with the application through menus and options.

### Utils

This folder contains helper functions and utilities shared across different parts of the project.

## Main Features

- User authentication
- Role-based access control
- Client management
- Employee management
- Deposit money
- Withdraw money
- Transfer money
- Search for clients
- Update client information
- PostgreSQL database integration

## Design Choices

While developing this project, I wanted the code to be modular and easy to extend. For this reason, I separated responsibilities into different layers instead of writing everything inside one file.

I also applied several Object-Oriented Programming concepts including inheritance, encapsulation, abstraction, and polymorphism. In addition, I followed SOLID principles whenever possible to improve code quality and maintainability.

Using PostgreSQL instead of storing information in files allowed the application to work with persistent data and better simulate a real banking system.

## Challenges

The biggest challenge during development was designing the architecture of the application while keeping the different components independent from each other.

Another challenge was connecting the application with PostgreSQL and organizing database operations in a clean way without mixing them with the business logic.

Managing multiple user roles and permissions also required careful planning to ensure that each user could only access the appropriate features.

## Future Improvements

Although the project is fully functional, there are several features that could be added in the future.

Some possible improvements include:

- Transaction history
- Account statements
- Interest calculations
- Password recovery
- Graphical User Interface (GUI)
- Online banking features
- Better reporting and statistics

## What I Learned

This project gave me practical experience in building a medium-sized software application. I improved my understanding of C++, object-oriented programming, database integration, software architecture, Git, and clean code organization.

Working on this project also taught me how to divide a large application into smaller, manageable components and how to design software that can be extended in the future without major modifications.
