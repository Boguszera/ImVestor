#include "TransactionManager.h"
#include <iostream>

bool TransactionManager::buyStock(User& user, Company* company, int shares) {
    double totalCost = shares * company->getStockPrice();
    if (user.getBalance() >= totalCost) {
        user.getPortfolio().addStock(company, shares);
        user.updateBalance(-totalCost);
        std::cout << "Bought " << shares << " shares of " << company->getName() << ".\n";
        return true;
    } else {
        std::cout << "Insufficient funds.\n";
        return false;
    }
}

bool TransactionManager::sellStock(User& user, Company* company, int shares) {
    double totalRevenue = shares * company->getStockPrice();
    user.getPortfolio().removeStock(company, shares);
    user.updateBalance(totalRevenue);
    std::cout << "Sold " << shares << " shares of " << company->getName() << ".\n";
    return true;
}
