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

struct Task
{
	int start;
	int step;
};

class ShellManager:public Manager
{
	public:
	ShellManager(int num_of_process):Manager(num_of_process)
	{

	}
	void WorkCycle();
};

void ShellManager::WorkCycle()
{
	int pid = getpid();
	//printf("In process %i\n", pid);
	char buf[80];
	read(pipes[0], buf, 3);
	//printf("id=%i\n", this->work_semid);
	while (buf[0] != 1)
	{
		//buf[0] = ' ';
		//buf[3] = 0;
		printf("str = %c\n", buf[1]);
		this->incsem(this->work_semid);
		//printf("Sem is increased %i\n", pid);
		read(pipes[0], buf, 3);
	}
	exit(0);
}

int createsem();
void delsem(int semid);
void incsem(int semid);
int waitsem(int semid, int num);

int childwork(int pipes[2]);

using namespace std;

int main(int argc, char** argv)
{
	key_t mykey = 12345678;
	const size_t region_size = 4096 + 10;//sysconf(_SC_PAGE_SIZE);
	int smid = shmget(mykey, region_size, IPC_CREAT | 0666);

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
		//printf("child wrote %#lx\n", *(u_long *) ptr);
		printf("child wrote %i\n", ((int *)ptr)[0]);
	}
	int r = shmdt(ptr);
	r = shmctl(smid, IPC_RMID, NULL);	

	
	int num_of_proc = 10;
	ShellManager man(num_of_proc);
	Task task;
	task.start = 1009;
	write(man.pipes[1], &task, sizeof(Task));
	task.start = 0;		
	read(man.pipes[0], &task, sizeof(Task));		
	printf("st=%i\n", task.start);
	return 0;
	//man.Start();

	char *s = "chanaler";
	char buf[80];
	for (int i = 0; i < 10; i += 2)
	{
		buf[0] = 0;
		buf[1] = 66 + (char)i % 254;
		buf[2] = s[i + 1];
		write(man.pipes[1], buf, 3);				
	}
	printf("Start wait\n");
	man.WaitForTaskEnd(5);
	printf("End wait\n");	
	//man.cursem++;
	for (int i = 0; i < 8; i += 2)
	{
		buf[0] = 0;
		buf[1] = 75 + (char)i % 254;
		buf[2] = s[i + 1];
		write(man.pipes[1], buf, 3);
	}
	printf("Start wait again\n");
	man.WaitForTaskEnd(4);
	printf("End wait\n");	

	s = "1";
	buf[0] = 1;
	buf[1] = 1;
	buf[2] = 0;
	for (int i = 0; i< num_of_proc; i++)
	{
		write(man.pipes[1], buf, 3);
	}
	
	man.Free();
	printf("the end\n");
	//make g++ happy
	return 0;	
	
}

