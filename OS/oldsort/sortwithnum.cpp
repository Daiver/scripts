#include <iostream>
#include <pthread.h>
//#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <math.h>
#include <vector>
#include <fstream>

#include <sys/stat.h>

extern "C"

using namespace std;

vector<float> *ReadFromFile(string filename);
void printarr(vector<float> *arr);
void shell(vector<float> *items, int num_of_threads);
vector<int> *GetSteps(int count);
void writetofile(char* fname, vector<float> *res);

class Task
{
    public:
    int start;
    int step;
    vector<float> *items;
};


class TaskManager
{
public:
    pthread_t *threads;
    queue<Task> tasks;
    queue<int> product;
    pthread_mutex_t taskmutex;
    pthread_mutex_t productmutex;
    TaskManager(int num_of_threads);
    bool finish;
};

Task taskfp(int start, int step, vector<float> *items)
{
    Task res;
    res.start = start;
    res.step = step;
    res.items = items;
    return res;
}

void *threadwork(void *data)
{
    TaskManager *tm = (TaskManager *)data;
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
                continue;
            }

            float x = (*tk.items)[tk.start];

            int j;
            for(j = tk.start - tk.step; (j >= 0) && (x < (*tk.items)[j]); j = j - tk.step)
            {

                (*tk.items)[j + tk.step] = (*tk.items)[j];
            }

            (*tk.items)[j + tk.step] = x;

            pthread_mutex_lock( &tm->productmutex );
            tm->product.push(1);
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
    this->threads = (pthread_t *)malloc(sizeof(pthread_t) * num_of_threads);
    int t, rc;
	for (t = 0; t < num_of_threads; t++)
	{
		rc = pthread_create(&threads[t], NULL, threadwork, (void *)this);
		if (rc)	{printf("error!");}
	}
}

int main(int argc, char** argv)
{
    if (argc != 4)
    {
    	cout<<"use with 4 args";
        return 0;
    }
    vector<float> *items = ReadFromFile(argv[1]);
    printarr(items);
    cout<<"sort\n";
    shell(items, atoi(argv[2]));
    printarr(items);
    writetofile(argv[3], items);
    return 0;
}

void shell(vector<float> *items, int num_of_threads)
{
    TaskManager tm(num_of_threads);
    vector<int> *steps = GetSteps(items->size());

    for (int t = steps->size() - 1; t >=0 ; t--)
    {
        int step = (*steps)[t];
        int j, counter = 0;
        //cout<<"Step : "<<step<<endl;
		for(int i = step; i < items->size(); ++i)
		{
		    counter++;
            vector<int> indexes;
            tm.tasks.push(taskfp(i, step, items));
		}
		while (tm.product.size() < counter)
		{
		    sleep(0);
		}
		tm.product = queue<int>();
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

vector<float> *ReadFromFile(string filename)
{
    struct stat filestatus;
    stat( filename.c_str(), &filestatus );
    int fsize = filestatus.st_size / sizeof(float);
    vector<float> *res = new vector<float>();
    ifstream fs;
    //int i = 1;
    fs.open(filename.c_str());
    float s;
    for (int i = 0; i < fsize; i++)
    {
        fs.read(reinterpret_cast<char*>(&s), sizeof(float));
        res->push_back(s);//cout<<s<<endl;
    }
    fs.close();
    return res;
}

void writetofile(char* fname, vector<float> *res)
{
        ofstream fs(fname, std::ios::out | std::ios::binary);
	for (int i = 0; i < res->size(); i++)
	{
		printf("writing %f\n", (*res)[i]);
		//Не, ну руки повыдергивать за это конечно можно
		fs.write((const char*) &(*res)[i], sizeof((*res)[i]));
	}
	fs.close();
    
}

void printarr(vector<float> *arr)
{
    for (int i = 0; i < arr->size(); i++)
        cout<<(*arr)[i]<<endl;
}


