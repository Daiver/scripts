
#include "ThreadPool.h"

#include <iostream>

ThreadPool::ThreadPool(int max_tasks_count)
{
    this->cur_index = 0;
    this->max_tasks_count = max_tasks_count;
    this->queue[4] = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0);
    this->queue[3] = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0);
    this->queue[2] = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    this->queue[1] = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0);
    this->queue[0] = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0);
    //dispatch_queue_create("com.mydomain.myapp.longrunningfunction", DISPATCH_QUEUE_CONCURRENT);
}

void ThreadPool::run_Operation_async(dispatch_group_t group, Operation *op)//this operation is NOT thread safe now, fix it!
{
    if (this->cur_tasks.size() >= this->max_tasks_count)
    {
        std::cout<<"Limit reached!"<<std::endl;
    }
    std::vector<Operation*> dependency = op->get_dependences();
    if (dependency.size() > 0) 
    {
        dispatch_group_t tmp_gr = dispatch_group_create();
        for(auto it = dependency.begin(); it != dependency.end(); ++it) {
            this->run_Operation_async(tmp_gr, *it);
        }
        dispatch_group_wait(tmp_gr, DISPATCH_TIME_FOREVER);
    }
    int index = this->cur_index++;
    cur_tasks.insert(index);
    dispatch_queue_t queue = this->queue[op->get_priority()];
    dispatch_group_async(group, queue, ^(void) {
        //std::cout<<"Start task #" << index << " s:" << cur_tasks.size() << std::endl;//<<std::cout.flush();
        op->Execute();
        cur_tasks.erase(index);
    });
}

void ThreadPool::async(Operation *op)
{
    dispatch_group_t group = dispatch_group_create();
    run_Operation_async(group, op);
}
