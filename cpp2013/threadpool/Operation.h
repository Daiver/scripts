#ifndef __OPERATION_H__
#define __OPERATION_H__

#include <vector>

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
    void add_dependency(Operation *op);
    std::vector<Operation*> get_dependences();
    long get_ID();
private:
    std::vector<Operation*> dependency;
    Operation_Priority priority;
    long id;
    static long get_new_ID()
    {
        static long inner_index = 0;
        return inner_index++;
    }

};
#else
#endif
