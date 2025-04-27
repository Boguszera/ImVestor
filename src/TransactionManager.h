// to manage transactions (buy, sell etc.)

#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include "User.h"

class TransactionManager {
public:
    static bool buyStock(User& user, Company* company, int shares);
    static bool sellStock(User& user, Company* company, int shares);
};

#endif