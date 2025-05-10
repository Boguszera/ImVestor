#include "Portfolio.h"
#include <iostream>
#include <algorithm>
#include <sstream>

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

std::string Portfolio::getPortfolio() const {
    std::ostringstream oss;  // Tworzymy obiekt ostringstream, który będzie buforował tekst
    
    if (holdings.empty()) {
        oss << "Portfolio is empty.\n";
    } else {
        for (const auto& holding : holdings) {
            oss << holding.getCompany()->getName() << " (" 
                << holding.getCompany()->getTicker() << "): " 
                << holding.getShares() << " shares\n";
        }
    }
    
    return oss.str();  // Zwracamy zawartość bufora jako string
}