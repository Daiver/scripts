
#include "ThreadPool.h"

ThreadPool::ThreadPool()
{
    this->queue[4] = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0);
    this->queue[3] = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0);
    this->queue[2] = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    this->queue[1] = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0);
    this->queue[0] = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0);
    //dispatch_queue_create("com.mydomain.myapp.longrunningfunction", DISPATCH_QUEUE_CONCURRENT);
}

void run_Operation_async(dispatch_queue_t queue, Operation *op)
{
    dispatch_async(queue, ^(void) {
        op->Execute();
    });
}

void ThreadPool::async(Operation *op)
{
    run_Operation_async(this->queue[op->get_priority()], op);
}
