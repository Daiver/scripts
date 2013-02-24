#ifndef __OPERATION_H__
#define __OPERATION_H__

enum Operation_Priority
{
    very_hight = 2,
    hight = 1,
    normal = 0,
    low = -1,
    very_low = -2
};

class Operation
{
public:
    virtual void Execute() = 0;
private:
    Operation_Priority priority;
};
#else
#endif
