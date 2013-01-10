#include "taskmanager.h"
#include <unistd.h>

struct InitContainer
{
    int *pipes;
    clientserv_f func;
    InitContainer(int *pipes, clientserv_f func)
    {
        this->pipes = pipes;
        this->func = func;
    }
};

void *ThreadFunc(void *initdata)
{
    InitContainer *cont = (InitContainer *)initdata;
    int *pipes = cont->pipes;
    Task tsk(false, NULL);
    while (!tsk.finish)
    {
        read(pipes[0], &tsk, sizeof(Task));
        cont->func(tsk.data);
    }
    delete cont;
}

int *ThreadPool::GetPipes()
{
    return this->pipes;
}

void ThreadPool::AddTask(Task t)
{
    write(this->pipes[1], &t, sizeof(Task));
}

ThreadPool::ThreadPool(int num_of_threads, clientserv_f func)
{
    pipe(this->pipes);
    this->num_of_threads = num_of_threads;
    for (int i = 0; i < this->num_of_threads; i++)
    {
        pthread_t thread;
        InitContainer *cont = new InitContainer(this->pipes, func);
        pthread_create(&thread, NULL, ThreadFunc, (void*)cont);
        this->threads.push_back(thread);
    }
}
