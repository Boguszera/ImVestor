#include <iostream>
#include "Company.h"
#include "User.h"
#include "TransactionManager.h"

int main(){
    // create a company
    Company test("Test", "TST", "test category", 127.25, 15000);

    test.printInfo();

    Company apple("Apple Inc.", "AAPL", "Technology", 150.0, 6543);
    Company tesla("Tesla Inc.", "TSLA", "Automotive", 700.0, 9935);

    User user("Jan Kowalski", 10000.0);

    user.printPortfolio();

    TransactionManager::buyStock(user, &apple, 50);
    TransactionManager::buyStock(user, &tesla, 10);

    user.printPortfolio();

    TransactionManager::sellStock(user, &apple, 20);

    user.printPortfolio();

    return 0;
}