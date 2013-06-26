#ifndef __OPERATION_H__
#define __OPERATION_H__

#include <vector>
#include <pthread.h>

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
    friend class ThreadPool;
    virtual void Execute() = 0;
    Operation_Priority get_priority();
    void set_priority(Operation_Priority priority);
    void add_dependency(Operation *op);
    long get_ID();
    Operation(const Operation &op)
    {
        this->dependency = op.dependency;
        this->id = get_new_ID();
    }
    
protected:
    std::vector<Operation*> get_dependences();
    std::vector<Operation*> dependency;
    Operation_Priority priority;
    long id;
    static long get_new_ID()
    {
        static long inner_index = 0;
        static pthread_mutex_t inner_mutex = PTHREAD_MUTEX_INITIALIZER;
        pthread_mutex_lock(&inner_mutex);
        long tmp = inner_index++;
        pthread_mutex_unlock(&inner_mutex);
        return tmp;
    }

};
#else
#endif
