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
    bool success = user.getPortfolio().removeStock(company, shares);
    if (success) {
        double totalRevenue = shares * company->getStockPrice();
        user.updateBalance(totalRevenue);  // Aktualizacja salda użytkownika
        std::cout << "Sold " << shares << " shares of " << company->getName() << ".\n";
        return true;  // Sprzedaż udana
    } else {
        std::cout << "You don't have enough shares to sell or no shares of this company in your portfolio.\n";
        return false;  // Sprzedaż nieudana
    }
}