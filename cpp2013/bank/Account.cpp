#include "Account.h"

Account::Account(unsigned long start_balance)
{
    this->money = start_balance;
}

unsigned long Account::get_Balance()
{
    return this->money;
}

