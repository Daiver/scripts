#ifndef EPOLLRECIVER_H
#define EPOLLRECIVER_H
#include "receiver.h"
#include "taskmanager.h"

#include <string>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <stdio.h>

class EpollReceiver : public Receiver
{
protected:
    int sfd, s;
    int efd;
    struct epoll_event event;
    struct epoll_event *events;
public:
    void Start(std::string port, ThreadPool pool);
    EpollReceiver();
};


#endif // EPOLLRECIVER_H
