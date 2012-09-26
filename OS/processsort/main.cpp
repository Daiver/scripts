#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <vector>
#include <stdio.h>

int childwork(int pipes[2]);

using namespace std;

int main(int argc, char** argv)
{
	int num_of_proc = 2;
	char *s = "chanel";
	char buf[80];
	int pipes[2];
	pipe(pipes);
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
	write(pipes[1], s,7 + 1);
	s = "1";
	for (int i = 0; i< num_of_proc; i++)
	{
		write(pipes[1], s, 1);
	}
	return 0;	
	
}

int childwork(int pipes[2])
{
	//printf("Hi!\n");
	char buf[80];
	read(pipes[0], buf, 1);
	while (buf[0] != '1')
	{
		buf[1] = 0;
		printf("%s\n", buf);
		read(pipes[0], buf, 1);
	}
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
