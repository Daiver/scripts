#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "taskmanager.h"
#include <vector>
#include <stdio.h>
#include <string>
#include <fstream>

struct Task
{
	int start;
	int step;
	bool finish;
};

class ShellManager:public Manager
{
	//protected:
		
	public:
		int smid;				
		int itemsize;
		size_t region_size;
		void *ptr;
		std::string **items;		
		int ReadFromFile(char* filename);
		ShellManager(int num_of_process):Manager(num_of_process)
		{
	
		}
		void WorkCycle();
};

void ShellManager::WorkCycle()
{
	int pid = getpid();
	Task task;
	read(pipes[0], &task, sizeof(Task));	
	int j;
	//std::string **items;
	//void *ptr;
	//key_t mykey = 123456780;
	std::string *x;	
//

	while (!task.finish)
	{		
		printf("st=%i step=%i \n", task.start, task.step);//, items[task.start]
		ptr = shmat(smid, NULL, SHM_RND);
		//printf("ptr=%i\n", *(int*)ptr);
		items = (std::string **)ptr;
		x = items[task.start];
		//printf("before loop %s\n", x->c_str());		
		for(j = task.start -  task.step; (j >= 0) && ((*x) < (*items[j])); j = j -  task.step)
            	{
                	items[j +  task.step] = items[j];
                	printf("s=%s\n", items[j +  task.step]->c_str());
            	}
		items[j + task.step] = x;
		int r = shmdt(ptr);
		printf("Sem is increased %i\n", pid);
		this->incsem(this->work_semid);
		read(pipes[0], &task, sizeof(Task));		
	}
}

//int createsem();
int ReadFromFile(char* filename);

using namespace std;

vector<int> &GetSteps(int count)
{
    vector<int> steps = new vector<int>();
    steps->push_back(1);
    steps->push_back(2);
    steps->push_back(3);
    steps->push_back(5);
    steps->push_back(9);
    return steps;
}

int main(int argc, char** argv)
{

	int num_of_proc = 911;
	ShellManager man(num_of_proc);
	Task task;
	man.ReadFromFile("input");
	man.Start();
	vector<int> steps = GetSteps(man.itemsize);
	for (int t = steps->size() - 1; t >=0 ; t--)
	{
		int step = (*steps)[t];
		int j, counter = 0;
		for(int i = step; i < man.itemsize; ++i)
		{
			counter++;
			task.start = i;
			task.step = step;
			write(man.pipes[1], &task, sizeof(Task));
		}
		man.WaitForTaskEnd(counter);
	}

	man.Free();
	man.ptr = shmat(man.smid, 0, 0);
	man.items = (string **) man.ptr;
	for (int i = 0; i < man.itemsize; i++)
	{
		printf("%i %s\n", i, man.items[i]->c_str());
	}
	printf("the end\n");
	//make g++ happy
	return 0;		
}


int ShellManager::ReadFromFile(char* filename)
{
	vector<string *> res;// = new vector<string *>();
	ifstream fs;
	fs.open(filename);
	string *s = new string();
	while (std::getline(fs, *s))// >> word)
	{
		res.push_back(s);
		s = new string();
	}

	fs.close();	
	//printf("size of str* %i\n", sizeof(string *));
	region_size = sizeof(string *) * res.size();//4096 + 10;//sysconf(_SC_PAGE_SIZE);
	this->smid = shmget(IPC_PRIVATE, region_size, 0666);//ipc_attach
	
	this->ptr = shmat(smid, 0, 0);
	this->items = (string **) ptr;
	//items = new string* [res.size()];
	itemsize = res.size();
	for (int i = 0; i < res.size(); i++)
	{
		items[i] = res[i];
		printf("2 str=%s\n", items[i]->c_str());
	}
	printf("in read ptr=%i\n", *(int*)ptr);
	int r = shmdt(ptr);
	printf("semid = %i\n", smid);	
	return 0;
}

/*
	void *ptr;
	ptr = shmat(smid, NULL, 0);
	pid_t pid = fork();
	if (pid == 0) {
		int *d = (int *) ptr;
		//*d = 0xdeadbeef;
		d[0] = 10;
		exit(0);
	}
	else {
		int status;
		waitpid(pid, &status, 0);
		printf("child wrote %i\n", ((int *)ptr)[0]);
	}
	int r = shmdt(ptr);
	r = shmctl(smid, IPC_RMID, NULL);	*/



/*	for (int i = 0; i < 8; i += 2)
	{
		task.start = i;
		task.step = 3;
		write(man.pipes[1], &task, sizeof(Task));
	}
	printf("Start wait\n");
	man.WaitForTaskEnd(4);
	printf("End wait\n");	
	
	for (int i = 0; i < 8; i += 2)
	{
		task.start = i;
		task.step = 222;
		write(man.pipes[1], &task, sizeof(Task));
	}
	man.WaitForTaskEnd(4);
*/	
