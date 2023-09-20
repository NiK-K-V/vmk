#include <stdio.h>

int main(void)
{
	unsigned int x, n, p, y;
	scanf("%d %d %d %d", &x, &n, &p, &y);
	y=~y;
	y>>=(32-n);
	y<<=(32-n-p+1);
	x=x|y;
	printf("%u\n", x);
	return 0;
}
