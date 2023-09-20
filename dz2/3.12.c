#include <stdio.h>
int main(void)
{
	int x, y, z;
	x=y=0;
	while(y<10)
		++y;
	x+=y;
	printf("x= %d y= %d \n", x, y);  //10, 10
	x=y=0;
	while(y<10)
		x+=++y;
	printf("x= %d y= %d \n", x, y);   //55, 10
	y=1;
	while(y<10)
	{
		x=y++;
		z=++y;
	}
	printf("x= %d y= %d z= %d \n", x, y, z);  //9, 11, 11
	for (y=1;y<10;y++)
		x=y;
	printf("x= %d y= %d \n", x, y);   //9, 10 - interesting
	for (y=1;(x=y)<10;y++);   
	printf("x= %d y= %d \n", x, y);   //10, 10
	for (x=0, y=1000;y>1;x++,y/=10)
	printf("x= %d y= %d \n", x, y);  //0, 1000  1, 100   2, 10
	return 0;
}
