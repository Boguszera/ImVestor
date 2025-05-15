#include "Company.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <random>
#include <algorithm>
#include <ctime>

Company::Company(const std::string& name, const std::string& ticker, const std::string& category, double stockPrice, int totalShares /* double marketCap */ )
    :name (name), ticker(ticker), category(category), stockPrice(stockPrice), totalShares(totalShares), lastPrice(stockPrice) {}

std::string Company::getName() const{
    return name;
}

std::string Company::getTicker() const{
    return ticker;
}

std::string Company::getCategory() const{
    return category;
}

double Company::getStockPrice() const{
    return stockPrice;
}

int Company::getTotalShares() const{
    return totalShares;
}

double Company::getMarketCap() const{
    return stockPrice * totalShares;
}

void Company::printInfo() const{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Firma: " << getName() << "\n"
                << ticker << "\n"
                << "Kategoria: " << getCategory() << "\n"
                << "Cena akcji: " << getStockPrice() << "\n"
                << "Liczba akcji: " << getTotalShares() << "\n"
                << "Kapitalizacja rynkowa: " << getMarketCap() << "\n\n";
}

void Company::initTrend() {
    static std::default_random_engine engine(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_real_distribution<double> initial(-2.0, 2.0);
    std::uniform_real_distribution<float> timeDist(5.0f, 30.0f);

    trendBias = initial(engine);
    nextTrendChangeTime = timeDist(engine);
}

void Company::updatePrice() {
    static std::default_random_engine engine(std::random_device{}());
    std::normal_distribution<double> noise(0.0, 2.0); // random noise

    lastPrice = stockPrice;
    double change = trendBias + noise(engine);
    stockPrice = std::max(0.0, stockPrice + change); // minimal price = 0.0
}

void Company::updateTrend() {
    if (trendClock.getElapsedTime().asSeconds() > nextTrendChangeTime) {
        static std::default_random_engine engine(std::random_device{}());
        std::normal_distribution<double> drift(0.0, 0.3); // mały dryf trendu
        std::uniform_real_distribution<float> timeDist(5.0f, 30.0f);

        trendBias += drift(engine);
        trendBias = std::clamp(trendBias, -3.0, 3.0); // ograniczamy siłę trendu

        trendClock.restart();
        nextTrendChangeTime = timeDist(engine);
    }
}

bool Company::didPriceIncrease() const {
    return stockPrice > lastPrice;
}

bool Company::didPriceDecrease() const {
    return stockPrice < lastPrice;
}