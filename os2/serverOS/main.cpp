
#include <stdio.h>
#include <pthread.h>
#include <string>
#include <vector>
#include <map>

#include "comandexecuter.h"
#include "taskmanager.h"
#include "epollreciver.h"

pthread_mutex_t sreadmutext;
pthread_mutex_t clientsmutex;

std::string tmppass = "123";

struct Client
{

};

std::map<int, Client*> clients;

void* ServeClient(void *d)
{
    std::string tmppass = "123";
    ComandExecuter CE;
    int fd = (long)d;
    printf("%d:%d receiv fd\n", pthread_self(), fd);
    char buf[512];
    memset(buf, 0, 512);
    //buf[0] = 0;
    pthread_mutex_lock(&sreadmutext);
    int count = recv(fd, buf, sizeof buf, 0);//read(fd, buf, sizeof buf);
    pthread_mutex_unlock(&sreadmutext);

    pthread_mutex_lock(&clientsmutex);
    std::map<int, Client*>::iterator it = clients.find(fd);
    if(it == clients.end())
    {
        std::string tmp  = buf;
        if (tmp.compare(tmppass))
        {
            printf("%d:%d reject client\n", pthread_self(), fd);
            send(fd, "NO", 3, 0);
            close(fd);
        }
        else
        {
            printf("%d:%d accept client\n", pthread_self(), fd);
            send(fd, "YES", 4, 0);
            clients[fd] = new Client();
        }
        pthread_mutex_unlock(&clientsmutex);
        return NULL;
    }
    else
    {
        pthread_mutex_unlock(&clientsmutex);
    }
    printf("%d:%d read %s\n", pthread_self(), fd, buf);
    std::vector<std::string> tmp = CE.Execute(std::string(buf));
    std::string result = "";
    for (int i = 0; i < tmp.size(); i++)
        result += tmp[i];

    send(fd, result.c_str(), strlen(result.c_str()), 0);



    //printf("%d:%d exec: %s\n", pthread_self(), fd, result.c_str());
    //write(fd, result.c_str(), strlen(result.c_str()));
    //if ((count == 0) || (strcmp("exit", buf))) {
        //printf("%d:Closing %d", pthread_self(), fd);
        //close(fd);
    //}
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("<usage> <port> <number_of_thread>\n");
        return 0;
    }

    pthread_mutex_init(&sreadmutext, NULL);
    pthread_mutex_init(&clientsmutex, NULL);

    ThreadPool tp(atoi(argv[2]), ServeClient);
    EpollReceiver er;
    er.Start(argv[1], tp);

    return 0;
}
