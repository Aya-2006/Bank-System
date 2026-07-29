## Bank System
#### Video Demo:  (https://www.youtube.com/watch?v=n8biUD9yHbk&list=PLaSv2mKcsbpDBS0pJSbA_Wt4_kFDai-4w&index=3)
#### Description:
A simple Bank Management System built with C++, following OOP and SOLID Principles, with PostgreSQL as the database.

- Features

## Client
  - Deposit
  - Withdraw
  - Transfer money

## Employee
  - Add clients
  - Search clients
  - Update client information

## Admin
  - All employee permissions
  - Manage employees

- Project Structure

```
models/         # Entities
repositories/   # Database layer
services/       # Business logic
ui/             # Console interface
```

## OOP Design

```
Person
├── Client
└── Employee
      └── Admin
```

## SOLID Principles

- SRP: Each class has a single responsibility.
- OCP: Easy to extend without modifying existing code.
- LSP: Any derived class can replace `Person`.
- ISP: Separate repository interfaces for each role.
- DIP: Services depend on interfaces, not PostgreSQL implementations.

## Database

- PostgreSQL
- libpq
- Transactions (`BEGIN`, `COMMIT`, `ROLLBACK`) for safe money transfers.

## Technologies

- C++
- OOP
- SOLID
- PostgreSQL
- CMake

## Build & Run

```bash
mkdir build
cd build
cmake ..
make
./bank_system
```
