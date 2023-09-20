#include <stdio.h>
#include <string.h>
int main(void)
{
	char s[100];
	int counter;
	fgets(s, 100, stdin);
	if (strchr(s, '.'))
	{
		for(int i=0;s[i]!='.';i++)
		{
			if(s[i]>='0' && s[i]<='9' && (s[i+1]<='0' || s[i+1]>='9'))
				printf("");
			else
			{
				if(s[i]<='0' || s[i]>='9')
					printf("%c", s[i]);
				else
				{
					for(counter=i;(s[counter+1]>s[counter]) && (s[counter+1]<='9');counter++);
					if(s[counter+1]<='0' || s[counter+1]>='9')
					{
						while(i<=counter)
						{
							printf("%c", s[i]);
							i++;
						}
						i--;
					}
					else
						while(i<=counter)
						{
							printf("");
							i++;
						}
				}
			}
		}
	}
	printf("\n");
	return(0);
}
