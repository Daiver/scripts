#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "taskmanager.h"
#include <vector>
#include <stdio.h>

class ShellManager:public Manager
{
	public:
	ShellManager(int num_of_process):Manager(num_of_process)
	{
	
	}
};

int createsem();
void delsem(int semid);
void incsem(int semid);
int waitsem(int semid, int num);

int childwork(int pipes[2]);

using namespace std;

int main(int argc, char** argv)
{
	int num_of_proc = 100;
	Manager man(num_of_proc);
	//man.Start();
	char *s = "chaneler";
	char buf[80];
	int pipes[2];
	pipe(pipes);
	int semid = createsem();
	incsem(semid);	
	waitsem(semid, 1);
	//sleep(1);
	incsem(semid);

	for (int i = 0; i< num_of_proc; i++)
	{
		int pid = fork();
		switch	(pid)
		{
			case 0:
				childwork(pipes);
				return 0;
			break;
			case -1:
				;//printf("ork error!!!");
			break;
			default:
				;
		}
	}
	//write(pipes[1], s,6 );
	for (int i = 0; i < 8; i += 2)
	{
		char buf[2];
		buf[0] = s[i];
		buf[1] = s[i + 1];		
		write(pipes[1], buf, 2);
	}
	s = "1";
	for (int i = 0; i< num_of_proc; i++)
	{
		write(pipes[1], s, 2);
	}
	delsem(semid);	
	printf("the end");
	man.Free();
	return 0;	
	
}

int childwork(int pipes[2])
{
	//printf("Hi!\n");
	char buf[80];
	read(pipes[0], buf, 2);
	while (buf[0] != '1')
	{
		buf[2] = 0;
		printf("%s\n", buf);
		read(pipes[0], buf, 2);
	}
}

void delsem(int semid)
{
	if((semctl(semid, 0, IPC_RMID)) < 0) { /* Удаление семафора */
		perror("semctl IPC_RMID");
		exit(EXIT_FAILURE);
	} else {
		puts("semaphore removed");
		//system("ipcs -s");
	}
}

int createsem()
{
	int semid;
	int nsems = 1;
	int flags = 0666;
	semid = semget(IPC_PRIVATE, nsems, flags);
	if(semid < 0) {
		perror("semget");
		exit(EXIT_FAILURE);
	}
	printf("semaphore created: %d\n", semid);
	return semid;
}

void incsem(int semid)
{
	struct sembuf buf;
	buf.sem_num = 0;
	buf.sem_op = 1;
	buf.sem_flg = IPC_NOWAIT; 
	if((semop(semid, &buf, 1)) < 0) {
		perror("semop");
		exit(EXIT_FAILURE);
	}
}

int waitsem(int semid, int num)
{
	struct sembuf buf;
	buf.sem_num = 0;
	buf.sem_op = -num;
	buf.sem_flg = 0;//SEM_UNDO; 
	if((semop(semid, &buf, 1)) < 0) {
		perror("semop");
		exit(EXIT_FAILURE);
	}
	return 0;
}













/*	int pid = fork();
	if (pid)
	{
		write(pipes[1], s,7 + 1);
	}
	else
	{
		read(pipes[0], buf, 7 + 1);
		printf("%s\n", buf);
		return 0;
	}
	close(pipes[0]);
	close(pipes[1]);
	printf("close\n");
	return 0;

	for (int i = 0; i < 5; i++)
	{
		int pid = fork();
		switch	(pid)
		{
			case 0:
				childwork();
				return 0;
			break;
			case -1:
				printf("fork error!!!");
			break;
			default:
				;
		}
	}
	return 0;*/
