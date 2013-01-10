#ifndef RECEIVER_H
#define RECEIVER_H
#include <string>

#include <taskmanager.h>

class Receiver
{
public:
    virtual void Start(std::string port, ThreadPool pool) = 0;
    Receiver();
};

#endif // RECEIVER_H
