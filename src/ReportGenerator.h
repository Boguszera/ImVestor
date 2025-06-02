#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <string>
#include "TransactionManager.h"

class ReportGenerator {
public:
    static void generateReport(const std::string& filename);
};

#endif