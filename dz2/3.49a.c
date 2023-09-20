#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	//char s[100];
	//fgets(s, 100, stdin);  так мы сможем ввести строку меньшего размера и уже проверять на точку
	int n;
	scanf("%d", &n);
	char *s;
	s = malloc(n*sizeof(char));
	for(int i=0;i<=n;i++)
	{  
		s[i]=getchar();
		if(s[i]=='.')
			break;
	}
	for(int i=0;i<=n;i++)
	{
		if(s[i]=='?')
			printf("!");
		else
			printf("%c", s[i]);	
	}
	printf("\n");
	free(s);
	return(0);
}
