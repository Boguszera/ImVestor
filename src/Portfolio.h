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
    void removeStock(Company* company, int shares);
};

#endif