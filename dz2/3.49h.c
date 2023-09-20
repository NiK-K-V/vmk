#include <stdio.h>
#include <string.h>
int main(void)
{
	char s[100];
	fgets(s, 100, stdin);
	//int x;
	//x=strlen(s)-2;
	if (strchr(s, '.'))
	{
		for(int i=0;s[i]!='.';i++)
		{
			if(s[i+1]=='.')
				printf("%c", s[i]);
			else
			{
				if(s[i]=='0' && (s[i-1]<'0' || s[i-1]>'9'))
				{
					while(s[i]=='0')
					{
						i++;
					}
					if(s[i]>='1' && s[i]<='9')
					{
						printf("%c", s[i]);
					}
					else
					{
						printf("0");
						if(s[i]=='.')
							break;
						else
						{
							printf("%c", s[i]);
						}
					}
				}
				else
					printf("%c", s[i]);
			}
		}
	}
	printf("\n");
	return(0);
}
