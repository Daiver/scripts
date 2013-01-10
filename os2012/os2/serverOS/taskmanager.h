#ifndef TASKMANAGER_H
#define TASKMANAGER_H
#include <pthread.h>
#include <vector>

#include "task.h"

typedef void* (*clientserv_f)(void *data);

class ThreadPool
{
protected:
    int pipes[2];
    int num_of_threads;
    std::vector<pthread_t> threads;
public:
    int* GetPipes();
    void AddTask(Task);
    ThreadPool(int, clientserv_f func);
};

#endif // TASKMANAGER_H
