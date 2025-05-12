// represents user data, his balance and manage his funds

#ifndef USER_H
#define USER_H

#include <string>
#include <Portfolio.h>

class User {
private:
    std::string name;
    double balance;
    Portfolio portfolio;

public:
    User(const std::string& name, double balance);

    std:: string getName() const;
    double getBalance() const;
    void updateBalance(double amount);
    Portfolio& getPortfolio();

    void printPortfolio() const;
};


#endif