#include "ReportGenerator.h"
#include "SystemMessage.h"
#include <fstream>
#include <iostream>
#include <iomanip>

void ReportGenerator::generateReport(const std::string& filename) {
    const auto& history = TransactionManager::getHistory();

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file to save report.\n";
        return;
    }

    file << "=== Transaction report ===\n\n";

    double totalProfitLoss = 0.0;

    file << std::left << std::setw(20) << "Date"
         << std::setw(10) << "Type"
         << std::setw(15) << "Company"
         << std::setw(10) << "Ticker"
         << std::setw(10) << "Quantity"
         << std::setw(15) << "Price/Un."
         << std::setw(15) << "Total"
         << std::setw(15) << "Profit/Loss"
         << "\n";

    file << std::string(110, '-') << "\n";

    for (const auto& record : history) {
        file << std::left
             << std::setw(20) << record.timestamp
             << std::setw(10) << record.type
             << std::setw(15) << record.companyName
             << std::setw(10) << record.ticker
             << std::setw(10) << record.quantity
             << std::setw(15) << std::fixed << std::setprecision(2) << record.pricePerUnit
             << std::setw(15) << record.totalAmount;

        if (record.type == "SELL") {
            file << std::setw(15) << record.profitOrLoss;
            totalProfitLoss += record.profitOrLoss;
        } else {
            file << std::setw(15) << "-";
        }
        file << "\n";
    }

    file << "\nTotal profit/loss: " << std::fixed << std::setprecision(2) << totalProfitLoss << " PLN\n";

    file.close();
    SystemMessage::set ("The report was saved to a file: " + filename);
}