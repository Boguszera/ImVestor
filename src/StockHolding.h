// represents single position in user portfolio (eg. 100 shares CompanyA)

#ifndef STOCKHOLDING_H
#define STOCKHOLDING_H

#include "Company.h"

class StockHolding {
private:
    Company* company;
    int shares;

public:
    StockHolding(Company* company, int shares);

    Company* getCompany() const;
    int getShares() const;

    void addShares(int additionalShares);
    void removeShares(int sharesToRemove);
    void printInfo() const;
};


#endif