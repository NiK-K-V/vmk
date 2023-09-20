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
			if(s[i]>'a' && s[i]<'z')
				printf("%c", s[i]);
		}
	}
	printf("\n");
	return(0);
}
