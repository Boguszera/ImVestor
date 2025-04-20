#include "User.h"
#include <iostream>

User::User(const std::string& name, double balance)
    : name(name), balance(balance) {}

double User::getBalance() const { return balance; }

void User::updateBalance(double amount) { balance += amount; }

Portfolio& User::getPortfolio() { return portfolio; }

void User::printPortfolio() const {
    std::cout << "User: " << name << "\n";
    portfolio.print();
    std::cout << "Balance: " << balance << "\n";
}
