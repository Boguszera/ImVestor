// to manage transactions (buy, sell etc.)

#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include "User.h"
#include <vector>
#include <string>

struct TransactionRecord {
    std::string companyName;
    std::string ticker;
    int quantity;
    double pricePerUnit;
    double totalAmount;
    std::string type; // "BUY", "SELL" or "Report"
    double profitOrLoss; // relevant only for SELL
    std::string timestamp;
};

class TransactionManager {
public:
    static bool buyStock(User& user, Company* company, int shares);
    static bool sellStock(User& user, Company* company, int shares);

    static const std::vector<TransactionRecord>& getHistory();

private:
    static std::vector<TransactionRecord> transactionHistory;
};

#endif