#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__
#include "Operation.h"
#include <dispatch/dispatch.h>

#include <set>

#define QUEUE_COUNT 5

class ThreadPool
{
public:
    ThreadPool(int max_tasks_count);
    void async(Operation *op);
private:
    void run_Operation_async(dispatch_group_t group, Operation *op);
    void run_Operation_async(Operation *op);
    bool is_ready_to_execute(Operation* op);
    dispatch_queue_t queue[QUEUE_COUNT];
    long max_tasks_count;
    int cur_index;
    std::set<long> cur_tasks;
    std::set<long> executed_tasks;
    std::set<Operation*> for_execute;
};
#else
#endif
