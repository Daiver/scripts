#include <iostream>

#include "Account.h"

int main(int argc, char** argv)
{
    Account ac1(90);
    Account ac2(40);
    std::cout<< "so..." << ac1.get_Balance() << " " << ac2.get_Balance() << "\n";
    return 0;
}
