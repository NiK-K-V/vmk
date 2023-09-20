#include <stdio.h>
#include <string.h>
int main(void)
{
	char s[100];
	fgets(s, 100, stdin);
	if (strchr(s, '.'))
	{
		for(int i=0;s[i]!='.';i++)
		{
			if(s[i]=='c' && s[i+1]=='h' && s[i+2]=='i' && s[i+3]=='l' && s[i+4]=='d')
			{
				printf("children");
				i+=4;
			}
			else
				printf("%c", s[i]);
		}
	}
	printf("\n");
	return(0);
}
