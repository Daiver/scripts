#ifndef TASK_H
#define TASK_H
struct Task
{
    bool finish;
    void *data;
    Task(bool finish, void* data)
    {
        this->finish = finish;
        this->data = data;
    }
};
#endif // TASK_H
