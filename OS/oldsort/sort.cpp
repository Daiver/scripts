#include <iostream>
#include <pthread.h>
//#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <math.h>
#include <vector>
#include <string>
#include <fstream>

extern "C"

using namespace std;

vector<string> *ReadFromFile(string filename);
void printarr(vector<string> *arr);
void shell(vector<string> *items, int num_of_threads);
vector<int> *GetSteps(int count);

struct Task
{
    //public:
    int start;
    int step;
    vector<string> *items;
};

class TaskManager
{
public:
    pthread_t *threads;
    queue<Task> tasks;
    queue<int> product;
    pthread_mutex_t taskmutex;
    pthread_mutex_t productmutex;
    pthread_mutex_t coutmutex;

    pthread_mutex_t taskcompletmutex;
    pthread_cond_t taskcomplete;
    TaskManager(int num_of_threads);
    bool finish;
};


class ThreadPacket
{
    public:
    int number;
    TaskManager* tm;
    ThreadPacket(int number, TaskManager* tm)
    {
        this->number = number;
        this->tm = tm;
    }
};


Task taskfp(int start, int step, vector<string> *items)
{
    Task res;
    res.start = start;
    res.step = step;
    res.items = items;
    return res;
}

void *threadwork(void *data)
{
    ThreadPacket *tp = (ThreadPacket *)data;
    TaskManager *tm = tp->tm; //= (TaskManager *)data;
    int id = tp->number;
    while (!tm->finish)
    {
        pthread_mutex_lock( &tm->taskmutex );

        if (!tm->tasks.empty())
        {
            Task tk = tm->tasks.front();
            tm->tasks.pop();
            pthread_mutex_unlock(&tm->taskmutex);
            if ((tk.start < 0) || (tk.start >= tk.items->size()))
            {
                tm->product.push(1);
                cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
                continue;
            }
            string x = (*tk.items)[tk.start];

            int j;
            //vector<int> tmp;
            /*cout<<"---------------\n";
            for(j = tk.start - tk.step; (j >= 0) && (x < (*tk.items)[j]); j = j - tk.step)
            {
                cout<<"id:"<<id<<"|"<<(*tk.items)[j]<<"|j="<<j<<"|x="<<x<<"|st="<<tk.start<<"|";
            }
            cout<<"\n---------------\n";*/
            for(j = tk.start - tk.step; (j >= 0) && (x < (*tk.items)[j]); j = j - tk.step)
            {

                (*tk.items)[j + tk.step] = (*tk.items)[j];
            }
            //cout<<"id is "<<id<<" placing x="<<x<<" place"<<j+tk.step<<"\n"<<flush;
            (*tk.items)[j + tk.step] = x;
            //cout<<"id is "<<id<<" now x="<<(*tk.items)[j + tk.step]<<"\n"<<flush;
            pthread_mutex_lock( &tm->coutmutex );
            cout<<"id "<<id<<" task: start "<<tk.start<<" step"<<tk.step<<"\n"<<flush;
            cout<<"j="<<j<<" x="<<x<<" place="<<j + tk.step<<"\n";
            cout<<"==================================\n";
            printarr(tk.items);
            cout<<"==============end==================\n";
            pthread_mutex_unlock( &tm->coutmutex );

            pthread_mutex_lock( &tm->productmutex );
            tm->product.push(1);
            pthread_cond_signal(&tm->taskcomplete);
            pthread_mutex_unlock( &tm->productmutex );
        }
        else{pthread_mutex_unlock(&tm->taskmutex);}
        sleep(0);
    }

    return NULL;
}


TaskManager::TaskManager(int num_of_threads)
{
    finish = false;
    taskmutex = PTHREAD_MUTEX_INITIALIZER;
    productmutex = PTHREAD_MUTEX_INITIALIZER;
    coutmutex = PTHREAD_MUTEX_INITIALIZER;

    taskcompletmutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_init(&this->taskcomplete, 0);
    this->threads = (pthread_t *)malloc(sizeof(pthread_t) * num_of_threads);
    int t, rc;
	for (t = 0; t < num_of_threads; t++)
	{
		//rc = pthread_create(&threads[t], NULL, threadwork, (void *)this);
		rc = pthread_create(&threads[t], NULL, threadwork, (void *)new ThreadPacket(t, this));
		if (rc)	{printf("error!");}
	}
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        cout<<"2 parametrs"<<endl;
        return 0;
    }
    int num_of_threads = atoi(argv[1]);
    vector<string> *items = ReadFromFile("input");
    printarr(items);
    cout<<"==============================start sort==============================\n";
    shell(items, num_of_threads);
    cout<<"==============================finish sort=================================\n";
    printarr(items);
    return 0;
}

void simplesort(vector<string> *items)
{
    int j;
    string x;
    for(int i = 1; i < items->size(); ++i)
    {
        x = (*items)[i];
        for(j = i - 1; (j >= 0) && (x < (*items)[j]); j--)
        {

            (*items)[j + 1] = (*items)[j];
        }
        (*items)[j + 1] = x;
    }
}

void shell(vector<string> *items, int num_of_threads)
{
    TaskManager tm(num_of_threads);
    vector<int> *steps = GetSteps(items->size());

    for (int t = steps->size() - 1; t >=0 ; t--)
    {
        int step = (*steps)[t];
        int j, counter = 0;
        cout<<"Step : "<<step<<endl;
		for(int i = step; i < items->size(); ++i)
		{
		    counter++;
            vector<int> indexes;
            tm.tasks.push(taskfp(i, step, items));
		}
		while (tm.product.size() < counter)
		{
		    pthread_cond_wait(&tm.taskcomplete, &tm.productmutex);
		    //pthread_cond_wait(&tm.taskcomplete, &tm.taskcompletmutex);
		    //sleep(0);
		}
		tm.product = queue<int>();
		//printarr(items);
    }
    tm.finish = true;
    int t;
  	for (t = 0; t < num_of_threads; t++)
  	{
  		pthread_join(tm.threads[t], NULL);
  	}
}

vector<int> *GetSteps(int count)
{
    vector<int> *steps = new vector<int>();
    steps->push_back(1);
    steps->push_back(2);
    steps->push_back(3);
    steps->push_back(5);
    steps->push_back(9);
    return steps;
}

vector<string> *ReadFromFile(string filename)
{
    vector<string> *res = new vector<string>();
    ifstream fs;
    //int i = 1;
    fs.open(filename.c_str());
    string s;
    cout<<"start\n";
    while (std::getline(fs, s))// >> word)
    {
        res->push_back(s);
    }
    fs.close();
    return res;
}

void printarr(vector<string> *arr)
{
    for (int i = 0; i < arr->size(); i++)
        cout<<i<<" "<<(*arr)[i]<<endl;
}


