#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <math.h>

#define N 10

double function(double x)
{
	return pow(x, 2);
}

int main()
{
	key_t key, key2, key3;
	key = ftok ("/bin/ls", 's');
	key2 = ftok ("/bin/ps", 's');
	key3 = ftok ("/bin/pwd", 's');
	
	int shmid, shmid2, shmid3;
	shmid = shmget(key, N, 0666 | IPC_CREAT);
	shmid2 = shmget(key2, N, 0666 | IPC_CREAT);
	shmid3 = shmget(key3, N, 0666 | IPC_CREAT);
	
	double *x, *F, *dF;
	x = shmat(shmid, NULL, 0);
	F = shmat(shmid2, NULL, 0);
	dF = shmat(shmid3, NULL, 0);
	
	for(int i=0; i < N; i++)
	{
		x[i] = i + 1;
	}
	for(int i=0; i < N; i++)
	{
		F[i] = function(x[i]);
	}
	
	if(fork()==0)
	{
		key_t key, key2;
		key = ftok ("/bin/ls", 's');
		key2 = ftok ("/bin/ps", 's');
		key3 = ftok ("/bin/pwd", 's');
		double h = 0.0001;
		
		int shmid, shmid2, shmid3;
		shmid = shmget(key, N, 0666 | IPC_CREAT);
		shmid2 = shmget(key2, N, 0666 | IPC_CREAT);
		shmid3 = shmget(key3, N, 0666 | IPC_CREAT);
		
		double *x, *F, *dF;
		x = shmat(shmid, NULL, SHM_RDONLY);
		F = shmat(shmid2, NULL, SHM_RDONLY);
		dF = shmat(shmid3, NULL, 0);
		
		for(int i=0; i < N / 2; i++)
		{
			if(i == 0)
			{
				dF[i] = (function(x[i] + h) - function(x[i])) / h;
			}
			else
			{
				dF[i] = (F[i+1] - F[i-1]) / (fabs(x[i + 1] - x[i - 1]));
			}
			//printf("%.2lf - %.2lf\n", x[i], dF[i]);
		}
		shmdt(x);
		shmdt(F);
		shmdt(dF);
		_exit(0);
	}
	if(fork()==0)
	{
		key_t key, key2, key3;
		key = ftok ("/bin/ls", 's');
		key2 = ftok ("/bin/ps", 's');
		key3 = ftok ("/bin/pwd", 's');
		double h = 0.0001;
		
		int shmid, shmid2, shmid3;
		shmid = shmget(key, N, 0666 | IPC_CREAT);
		shmid2 = shmget(key2, N, 0666 | IPC_CREAT);
		shmid3 = shmget(key3, N, 0666 | IPC_CREAT);
		
		double *x, *F, *dF;
		x = shmat(shmid, NULL, SHM_RDONLY);
		F = shmat(shmid2, NULL, SHM_RDONLY);
		dF = shmat(shmid3, NULL, 0);
		
		for(int i = N / 2; i < N; i++)
		{
			if(i == (N - 1))
			{
				dF[i] = (function(x[i] + h) - function(x[i])) / h;
			}
			else
			{
				dF[i] = (F[i+1] - F[i-1]) / (fabs(x[i + 1] - x[i - 1]));
			}
			//printf("%.2lf - %.2lf\n", x[i], dF[i]);
		}
		shmdt(x);
		shmdt(F);
		shmdt(dF);
		_exit(0);
	}
	wait(NULL);
	wait(NULL);
	printf("Function - x^2 \n");
	printf("Derivative - 2x \n");
	for(int i=0; i < N; i++)
	{
		printf("x: %.2lf - F(x): %.2lf - F'(x): %.2lf\n", x[i], F[i], dF[i]);
	}
	shmdt(x);
	shmdt(F);
	shmdt(dF);
	shmctl(shmid, IPC_RMID, NULL);
	shmctl(shmid2, IPC_RMID, NULL);
	shmctl(shmid3, IPC_RMID, NULL);
	return 0;
}
