#include <stdio.h>
int main(void)
{
	//если написать int i, char c до for, то ошибки не будет, но так тоже работает
	for(int i=0, char c=getchar();c!=' ' && c!='\n' && c!='\t' && c!=EOF;i++, c=getchar());
	printf("%d \n", i);
	return 0;	
}

