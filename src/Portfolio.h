// represents whole positions (shares) in user portfolio

#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <vector>
#include "StockHolding.h"

class Portfolio {
private:
    std::vector<StockHolding> holdings;

public:
    std:: string getPortfolio() const;
    void addStock(Company* company, int shares);
    bool removeStock(Company* company, int shares);
};

#endif