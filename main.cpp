#include <iostream>
#include "Company.h"

int main(){
    // create a company
    Company test("Test", "TST", "test category", 127.25, 15000);

    test.printInfo();

    return 0;
}