#ifndef COMPANY_H
#define COMPANY_H

#include <string>
#include <SFML/System.hpp>
#include <vector>

class Company {
private:
    std::string name;
    std::string ticker;
    std::string category;
    double stockPrice;
    int totalShares;

    // fields for trend simulation
    double trendBias = 0.0;
    sf::Clock trendClock;
    float nextTrendChangeTime = 0.0f;

    double lastPrice;
    std::vector<float> priceHistory;

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
    const std::vector<float>& getPriceHistory() const;

    void printInfo() const;

    // trend methods
    void initTrend();
    void updatePrice();
    void updateTrend();

    bool didPriceIncrease() const;
    bool didPriceDecrease() const;
};

#endif