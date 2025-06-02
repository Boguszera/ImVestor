#include "TransactionManager.h"
#include "SystemMessage.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

std::vector<TransactionRecord> TransactionManager::transactionHistory;

std::string getCurrentTimestamp() {
    std::time_t now = std::time(nullptr);
    std::tm* tm = std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

bool TransactionManager::buyStock(User& user, Company* company, int shares) {
    double price = company->getStockPrice();
    double totalCost = shares * company->getStockPrice();

    if (user.getBalance() >= totalCost) {
        user.getPortfolio().addStock(company, shares);
        user.updateBalance(-totalCost);
        SystemMessage::set("Bought " + std::to_string(shares) + " shares of " + company->getName());
        TransactionRecord record;
        record.companyName = company->getName();
        record.ticker = company->getTicker();
        record.quantity = shares;
        record.pricePerUnit = price;
        record.totalAmount = totalCost;
        record.type = "BUY";
        record.profitOrLoss = 0.0;
        record.timestamp = getCurrentTimestamp();
        transactionHistory.push_back(record);

        return true;
    } else {
        SystemMessage::set("Insufficient funds");
        return false;
    }
}

bool TransactionManager::sellStock(User& user, Company* company, int shares) {
    bool success = user.getPortfolio().removeStock(company, shares);
    if (success) {
        double price = company->getStockPrice();
        double totalRevenue = shares * price;
        user.updateBalance(totalRevenue);  

    // cost of buying sold shares (FIFO from BUY history)
        int remainingToMatch = shares;
        double totalCost = 0.0;

        for (TransactionRecord& record : transactionHistory) {
            if (record.type == "BUY" && record.ticker == company->getTicker() && record.quantity > 0) {
                int matchedShares = std::min(remainingToMatch, record.quantity);
                totalCost += matchedShares * record.pricePerUnit;
                record.quantity -= matchedShares;
                remainingToMatch -= matchedShares;

                if (remainingToMatch == 0) break;
            }
        }

        if (remainingToMatch > 0) {
            SystemMessage::set ("Warning: Unable to find matching BUY transactions for all shares");
        }

        double profit = totalRevenue - totalCost;

        SystemMessage::set("Sold " + std::to_string(shares) + " shares of " + company->getName());

        TransactionRecord record;
        record.companyName = company->getName();
        record.ticker = company->getTicker();
        record.quantity = shares;
        record.pricePerUnit = price;
        record.totalAmount = totalRevenue;
        record.type = "SELL";
        record.profitOrLoss = profit;
        record.timestamp = getCurrentTimestamp();
        transactionHistory.push_back(record);
        return true;  
    } else {
        SystemMessage::set ("You don't have enough shares to sell or no shares of this company in your portfolio");
        return false; 
    }
}

const std::vector<TransactionRecord>& TransactionManager::getHistory() {
    return transactionHistory;
}