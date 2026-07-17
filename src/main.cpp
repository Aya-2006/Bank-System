#include "repositories/postgres/PGConnection.h"
#include "repositories/postgres/PostgresClientRepository.h"
#include "repositories/postgres/PostgresEmployeeRepository.h"
#include "repositories/postgres/PostgresAdminRepository.h"
#include "repositories/postgres/PostgresTransactionManager.h"
#include "services/AuthService.h"
#include "services/BankingService.h"
#include "services/ClientManagementService.h"
#include "services/EmployeeManagementService.h"
#include "ui/Screens.h"

int main() {
    
    PGConnection& database = PGConnection::getInstance(
        "localhost", "5432", "bank_system"); 
    PostgresClientRepository clientRepo(database.getHandle());
    PostgresEmployeeRepository employeeRepo(database.getHandle());
    PostgresAdminRepository adminRepo(database.getHandle());
    PostgresTransactionManager txManager(database.getHandle());

    AuthService authService(clientRepo, employeeRepo, adminRepo);
    BankingService bankingService(clientRepo, txManager);
    ClientManagementService clientMgmtService(clientRepo);
    EmployeeManagementService employeeMgmtService(employeeRepo);

    Screens::runApp(authService, bankingService, clientMgmtService, employeeMgmtService,
                     clientRepo, employeeRepo, adminRepo);

    return 0;
}
