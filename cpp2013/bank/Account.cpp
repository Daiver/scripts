#include "Account.h"

Account::Account(unsigned long start_balance)
{
    this->money = start_balance;
}

Account::Account()
{
    this->money = 0;
}

bool Account::transfer_money_to(Account *reciver, unsigned long count)
{
    if (this->money < count) 
    {
        return false;
    }
    this->money -= count;
    reciver->money += count;
    return true;
}

unsigned long Account::get_Balance()
{
    return this->money;
}

