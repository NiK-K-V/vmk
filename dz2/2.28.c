#include <stdio.h>
int main(void)
{
int n, num;
scanf("%d %d", &num, &n);
for (int k=0;k<n;k++)
	num=num>>1;
printf("%d \n", num);
}
