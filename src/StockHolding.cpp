#include "StockHolding.h"
#include <iostream>

StockHolding::StockHolding(Company* company, int shares)
    : company(company), shares(shares) {}

Company* StockHolding::getCompany() const { return company; }
int StockHolding::getShares() const { return shares; }

void StockHolding::addShares(int additionalShares) { shares += additionalShares; }
void StockHolding::removeShares(int sharesToRemove) { shares -= sharesToRemove; }

void StockHolding::printInfo() const {
    std::cout << company->getName() << " (" << company->getTicker() << "): "
              << shares << " shares\n";
}