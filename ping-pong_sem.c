#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <math.h>
#include <sys/sem.h>
#include <signal.h>
#define MAX_NUMBER 100

int main()
{
	pid_t pid;
	if((pid=fork()) == 0)   //сын
	{
		key_t key;
		int shmid, semid;
		int *a;
		struct sembuf sops;
		key = ftok ("/bin/ls", 's');
		shmid = shmget(key, 1, 0666 | IPC_CREAT);
		a = shmat(shmid, NULL, 0);
		semid = semget(key, 1, 0666 | IPC_CREAT);
		sops.sem_num = 0;
		sops.sem_flg = 0;
		while(*a < MAX_NUMBER)
		{
			sops.sem_op = -2;
			semop(semid, &sops, 1);
			*a += 1;
			printf("Son: %d \n", *a);
			sops.sem_op = -1;
			semop(semid, &sops, 1);
		}
		
		shmdt(a);
		_exit(0);
	}
	else     //отец
	{
		key_t key;
		int shmid, semid;
		int *a;
		struct sembuf sops;
		key = ftok ("/bin/ls", 's');
		shmid = shmget(key, 1, 0666 | IPC_CREAT);
		a = shmat(shmid, NULL, 0);
		semid = semget(key, 1, 0666 | IPC_CREAT);
		semctl(semid, 0, SETVAL, (int) 0);
		sops.sem_num = 0;
		sops.sem_flg = 0;
		printf("Start Number: ");
		scanf("%d", a);
		while(*a < MAX_NUMBER)
		{
			*a += 1;
			printf("Father: %d \n", *a);
			if(*a == MAX_NUMBER)
			{
				break;
			}
			sops.sem_op = 3;
			semop(semid, &sops, 1);
			
			sops.sem_op = 0;
			semop(semid, &sops, 1);
		}
		
		kill(pid, SIGINT);
		wait(NULL);
		shmdt(a);
		shmctl(shmid, IPC_RMID, NULL);
		semctl(semid, 0, IPC_RMID, (int) 0);
	}
	return 0;
}
