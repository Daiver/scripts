
#include "ThreadPool.h"

ThreadPool::ThreadPool()
{
    for(int i = 0; i < QUEUE_COUNT; i++)
    {
        this->queue[i] = dispatch_queue_create("com.mydomain.myapp.longrunningfunction", DISPATCH_QUEUE_CONCURRENT);
    }
}

void run_Operation_async(dispatch_queue_t queue, Operation *op)
{
    dispatch_async(queue, ^(void) {
        op->Execute();
    });
}

void ThreadPool::async(Operation *op)
{
    run_Operation_async(this->queue[2], op);
}
