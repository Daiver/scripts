#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__
#include "Operation.h"
#include <dispatch/dispatch.h>

#define QUEUE_COUNT 5

class ThreadPool
{
public:
    ThreadPool();
    void async(Operation *op);
private:
    dispatch_queue_t queue[QUEUE_COUNT];
};
#else
#endif
