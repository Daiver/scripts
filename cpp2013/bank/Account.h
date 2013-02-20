class Account
{
public:
    Account(unsigned long start_balance);
    Account();
    unsigned long get_Balance();
    bool transfer_money_to(Account *reciver, unsigned long count);
private:
    unsigned long money;
};
