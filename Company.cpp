#include "Company.h"
#include <iostream>
#include <iomanip>

Company::Company(const std::string& name, const std::string& ticker, const std::string& category, double stockPrice, int totalShares, /* double marketCap */ )
    :name (name), ticker(ticker), category(category), stockPrice(stockPrice), totalShares(totalShares) /*, marketCap(marketCap) */ {}

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

/*void Company::updatePrice(double percentChange) {
    stockPrice *= (1 + percentChange / 100.0);
} */

void Company::printInfo() const{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Firma: " << getName() << "\n"
                << ticker << "\n"
                << "Kategora: " << getCategory() << "\n"
                << "Cena akcji: " << getStockPrice() << "\n"
                << "Liczba akcji: " << getTotalShares() << "\n"
                << "Kapitalizacja rynkowa: " << getMarketCap() << "\n\n";
}
