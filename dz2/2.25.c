#include <stdio.h>
int main(void)
{
	unsigned int a=0;
	int n, i;
	for(i=0;i<4;i++)
	{
		scanf("%d", &n);
		a=a*10+n;
	}
	printf("%u \n", a);
	return 0;
}
