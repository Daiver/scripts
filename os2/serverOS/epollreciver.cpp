#include "epollreciver.h"
#include "task.h"

#define MAXEVENTS 64

int create_and_bind (const char *port);
int make_socket_non_blocking (int sfd);


void EpollReceiver::Start(std::string port, ThreadPool pool)
{
    char *newport = (char *)port.c_str();
    sfd = create_and_bind (newport);
    if (sfd == -1)
        abort ();

    s = make_socket_non_blocking (sfd);
    if (s == -1)
        abort ();

    s = listen (sfd, SOMAXCONN);//start listinig socket
    if (s == -1)
    {
        perror ("listen");
        abort ();
    }

    efd = epoll_create1 (0);//create epoll
    if (efd == -1)
    {
        perror ("epoll_create");
        abort ();
    }

    event.data.fd = sfd;
    event.events = EPOLLIN | EPOLLET | EPOLLPRI;
    s = epoll_ctl (efd, EPOLL_CTL_ADD, sfd, &event);//add sfd
    if (s == -1)
    {
        perror ("epoll_ctl");
        abort ();
    }

    /* Buffer where events are returned */
    events = (struct epoll_event *)calloc (MAXEVENTS, sizeof event);

    /* The event loop */
    while (1)
    {
        int n, i;
        n = epoll_wait (efd, events, MAXEVENTS, -1);
        for (i = 0; i < n; i++)
        {
            if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || (!(events[i].events & EPOLLIN)))
            {//error catch (maybe k chertu?)
                fprintf (stderr, "epoll error %d\n", events[i].data.fd);
                epoll_ctl(efd, EPOLL_CTL_DEL, sfd, &event);
                close (events[i].data.fd);
                continue;
            }
            else if (events[n].events & EPOLLRDHUP)
            {
                epoll_ctl(efd, EPOLL_CTL_DEL, sfd, &event);
                //--events_count;
                printf ("Closed connection on descriptor %d\n",
                        events[i].data.fd);
                close(events[i].data.fd);
                continue;
            }
            else if (sfd == events[i].data.fd)
            {
                /* We have a notification on the listening socket, which
                   means one or more incoming connections. */
                while (1)
                {
                    struct sockaddr in_addr;
                    socklen_t in_len;
                    int infd;
                    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

                    in_len = sizeof in_addr;
                    infd = accept (sfd, &in_addr, &in_len);
                    if (infd == -1)
                    {
                        if ((errno == EAGAIN) ||
                                (errno == EWOULDBLOCK))
                        {
                            /* We have processed all incoming
                               connections. */
                            break;
                        }
                        else
                        {
                            perror ("accept");
                            break;
                        }
                    }

                    s = getnameinfo (&in_addr, in_len,
                                     hbuf, sizeof hbuf,
                                     sbuf, sizeof sbuf,
                                     NI_NUMERICHOST | NI_NUMERICSERV);
                    if (s == 0)
                    {
                        printf("Accepted connection on descriptor %d "
                               "(host=%s, port=%s)\n", infd, hbuf, sbuf);
                    }

                    /* Make the incoming socket non-blocking and add it to the
                       list of fds to monitor. */
                    s = make_socket_non_blocking (infd);
                    if (s == -1)
                        abort ();

                    event.data.fd = infd;
                    event.events = EPOLLIN | EPOLLET;
                    s = epoll_ctl (efd, EPOLL_CTL_ADD, infd, &event);
                    if (s == -1)
                    {
                        perror ("epoll_ctl");
                        abort ();
                    }
                }
                continue;
            }
            else
                /*
                 * Workin here
                */
            {

                Task tsk(false, (void *)events[i].data.fd);
                pool.AddTask(tsk);
                /*if (done)
                {
                    printf ("Closed connection on descriptor %d\n",
                            events[i].data.fd);

                    close (events[i].data.fd);
                }*/
            }
        }
    }

    free (events);

    close (sfd);

    //return EXIT_SUCCESS;
}

int make_socket_non_blocking (int sfd)
{
    int flags, s;

    flags = fcntl (sfd, F_GETFL, 0);
    if (flags == -1)
    {
        printf ("fcntl");
        return -1;
    }

    flags |= O_NONBLOCK;
    s = fcntl (sfd, F_SETFL, flags);
    if (s == -1)
    {
        perror ("fcntl");
        return -1;
    }

    return 0;
}

int create_and_bind (const char *port)
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int s, sfd;

    memset (&hints, 0, sizeof (struct addrinfo));
    hints.ai_family = AF_UNSPEC; /* Return IPv4 and IPv6 choices */
    hints.ai_socktype = SOCK_STREAM; /* We want a TCP socket */
    hints.ai_flags = AI_PASSIVE; /* All interfaces */

    s = getaddrinfo (NULL, port, &hints, &result);
    if (s != 0)
    {
        fprintf (stderr, "getaddrinfo: %s\n", gai_strerror (s));
        return -1;
    }
    int counter = 0;
    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        counter++;
        sfd = socket (rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1)
            continue;

        s = bind (sfd, rp->ai_addr, rp->ai_addrlen);
        if (s == 0)
        {
            /* We managed to bind successfully! */
            break;
        }
        printf("adress already in use :%d\n", s);
        close (sfd);
    }
    printf("num_of_addrinfo %d\n", counter);
    if (rp == NULL)
    {
        fprintf (stderr, "Could not bind\n");
        return -1;
    }

    freeaddrinfo (result);

    return sfd;
}

EpollReceiver::EpollReceiver()
{
}
