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
			if(s[i]=='t' && s[i+1]=='h' && s[i+2]=='e')
			{
				printf("");
				i=i+2;
			}
			else
			{
				printf("%c", s[i]);
			}
		}
	}
	printf("\n");
	return(0);
}
