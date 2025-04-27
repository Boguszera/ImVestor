#ifndef COMPANY_H
#define COMPANY_H

#include <string>

class Company {
private:
    std::string name;
    std::string ticker;
    std::string category;
    double stockPrice;
    int totalShares;

public:
    // constructor
    Company(const std::string& name, const std::string& ticker, const std::string& category, double stockPrice, int totalShares);

    // getters
    std:: string getName() const;
    std:: string getTicker() const;
    std:: string getCategory() const;
    double getStockPrice() const;
    int getTotalShares() const;
    double getMarketCap() const;

    // simulation of changes
    /*
    void updatePrice(double percentChange);
    */

    void printInfo() const;
};

#endif