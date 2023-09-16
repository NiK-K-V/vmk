#include <stdio.h>
int main(void)
{
	int n, m, flag, check;
	scanf("%d", &n);
	check=n;
	flag=0;
	while(n>0)
	{
		m=0;
		while(m<(2+flag))
		{
			for(int x=0;x<(check-m);x++)
			{
				printf(" ");
			}
			for(int j=0;j<(1+2*m);j++)
			{
				printf("*");
			}
		printf("\n");
		m++;
		}
	flag++;
	n--;
	}
	return 0;
}
