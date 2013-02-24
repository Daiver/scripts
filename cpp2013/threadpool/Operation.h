#ifndef __OPERATION_H__
#define __OPERATION_H__

enum Operation_Priority
{
    very_hight = 4,
    hight = 3,
    normal = 2,
    low = 1,
    very_low = 0
};

class Operation
{
public:
   virtual void Execute() = 0;
   Operation_Priority get_priority();
   void set_priority(Operation_Priority priority);
private:
    Operation_Priority priority;
};
#else
#endif
