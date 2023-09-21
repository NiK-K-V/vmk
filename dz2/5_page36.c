#include <stdio.h>
#include <stdlib.h>
#define n 10

int main(void)
{
	double x[n];
	for(int i=0;i<n;i++)
		x[i] = (double) rand() / (RAND_MAX / 100) - 50;
	for(int i=0;i<n;i++)
		printf("%lf \n", x[i]);
	for(int i=0;i<n;i++)
		if(x[i]<0)
			x[i]=-x[i];
	printf("---------- \n");
	for(int i=0;i<n;i++)
		printf("%lf \n", x[i]);	
	return 0;
}
