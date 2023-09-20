#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
int main(void)
{
	char s[100];
	fgets(s, 100, stdin);  //так мы сможем ввести строку меньшего размера и уже проверять на точку
	/*int n;
	scanf("%d", &n);
	char *s;							можно и так, но неудобно
	s = malloc(n*sizeof(char));  
	for(int i=0;s[i]!='.';i++)
	{  
		s[i]=getchar();
		if(s[i]=='.')
			break;
	}  */
	if (strchr(s, '.'))
	{
		for(int i=0;s[i]!='.';i++)
		{
			if(s[i]=='?')
				printf("!");
			else
				printf("%c", s[i]);	
		}
	}
	printf("\n");
	//free(s);
	return(0);
}
