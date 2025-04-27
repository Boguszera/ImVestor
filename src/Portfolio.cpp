#include "Portfolio.h"
#include <iostream>
#include <algorithm>

void Portfolio::addStock(Company* company, int shares) {
    auto it = std::find_if(holdings.begin(), holdings.end(), [&](const StockHolding& holding) {
        return holding.getCompany()->getTicker() == company->getTicker();
    });

    if (it != holdings.end()) {
        it->addShares(shares);
    } else {
        holdings.emplace_back(company, shares);
    }
}

void Portfolio::removeStock(Company* company, int shares) {
    auto it = std::find_if(holdings.begin(), holdings.end(), [&](const StockHolding& holding) {
        return holding.getCompany()->getTicker() == company->getTicker();
    });

    if (it != holdings.end()) {
        if (it->getShares() >= shares) {
            it->removeShares(shares);
            if (it->getShares() == 0) {
                holdings.erase(it);
            }
        } else {
            std::cerr << "Not enough shares to sell.\n";
        }
    } else {
        std::cerr << "No shares of this company in portfolio.\n";
    }
}

void Portfolio::print() const {
    if (holdings.empty()) {
        std::cout << "Portfolio is empty.\n";
    } else {
        for (const auto& holding : holdings) {
            holding.printInfo();
        }
    }
}