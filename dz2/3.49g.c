#include <stdio.h>
#include <string.h>
int main(void)
{
	char s[100];
	int counter=0;
	fgets(s, 100, stdin);
	if (strchr(s, '.'))
	{
		for(int i=0;s[i]!='.';i++)
		{
			if(s[i]=='*')
			{
				counter=1;
				if(s[i+1]!='*')
					printf("%c", s[i]);
				else
				{
					while(s[i]=='*')
					{
						counter++;
						i++;
					}
					counter--;
					counter/=2;
					i--;
					for(int j=0;j<counter;j++)
						printf("+");
				}
			}
			else
				printf("%c", s[i]);
		}
	}
	printf("\n");
	return(0);
}
