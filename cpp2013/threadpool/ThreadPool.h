#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__
#include "Operation.h"
#include <dispatch/dispatch.h>

class ThreadPool
{
public:
    ThreadPool();
    void async(Operation *op);
private:
    dispatch_queue_t queue;
};
#else
#endif
