
#include "ThreadPool.h"

ThreadPool::ThreadPool()
{
    this->queue = dispatch_queue_create("com.mydomain.myapp.longrunningfunction", DISPATCH_QUEUE_CONCURRENT);
}

void run_Operation_async(dispatch_queue_t queue, Operation *op)
{
    dispatch_async(queue, ^(void) {
        op->Execute();
    });
}

void ThreadPool::async(Operation *op)
{
    run_Operation_async(this->queue, op);
}
