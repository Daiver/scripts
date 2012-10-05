
class Manager
{
	protected:		
		int work_semid;//semaphoreid
		int createsem(int num);
		void delsem(int semid);
		void incsem(int semid);
		int waitsem(int semid, int num);
		int num_of_process;
		int last_sem_ind;

	public:
		int cursem;
		int pipes[2];//pipes :)
		Manager(int num_of_process);
		void Free();		
		void Start();
		void WaitForTaskEnd(int tasksize);
		virtual void WorkCycle();
};

void Manager::WaitForTaskEnd(int tasksize)
{
	waitsem(this->work_semid, tasksize);
	this->last_sem_ind += tasksize;
}

void Manager::Free()
{
	this->delsem(this->work_semid);
}

void Manager::WorkCycle()
{
	exit(0);
}

Manager::Manager(int num_of_process)
{
	this->num_of_process = num_of_process;
	this->cursem = 0;
	pipe(pipes);
	this->work_semid = createsem(1);	
	this->last_sem_ind = 0;
}


void Manager::Start()
{
	for (int i = 0; i< num_of_process; i++)
	{
		int pid = fork();
		switch	(pid)
		{
			case 0:
				WorkCycle();
				return;
			break;
			case -1:
				;//printf("ork error!!!");
			break;
			default:
				;
		}
	}
}

void Manager::delsem(int semid)
{
	if((semctl(semid, 0, IPC_RMID)) < 0) { /* Удаление семафора */
		perror("semctl IPC_RMID");
		exit(EXIT_FAILURE);
	} else {
		puts("semaphore removed");
		//system("ipcs -s");
	}
}

int Manager::createsem(int nsems)
{
	int semid;
	//int nsems = 1;
	int flags = 0666;
	semid = semget(IPC_PRIVATE, nsems, flags);
	if(semid < 0) {
		perror("semget");
		exit(EXIT_FAILURE);
	}
	//printf("semaphore created: %d\n", semid);
	return semid;
}

void Manager::incsem(int semid)
{
	struct sembuf buf;
	buf.sem_num = this->cursem;
	buf.sem_op = 1;
	buf.sem_flg = IPC_NOWAIT; 
	if((semop(semid, &buf, 1)) < 0) {
		perror("semop");
		exit(EXIT_FAILURE);
	}
}

int Manager::waitsem(int semid, int num)
{
	struct sembuf buf;
	buf.sem_num = this->cursem;
	buf.sem_op = -num;
	buf.sem_flg = 0;//SEM_UNDO; 
	if((semop(semid, &buf, 1)) < 0) {
		perror("semop");
		exit(EXIT_FAILURE);
	}
	return 0;
}

