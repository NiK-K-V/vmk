#include <stdio.h>
int main(void)
{
	unsigned int n;
	int a, b, c, d;
	scanf("%u", &n);
	a=n%10;
	n=n/10;
	b=n%10;
	n=n/10;
	c=n%10;
	n=n/10;
	d=n%10;
	printf("%d%d%d%d", d, c, b, a);
	return 0;
}
