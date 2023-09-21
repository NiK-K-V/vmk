#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define n 100
int main(void)
{
	char s[n];
	fgets(s, n, stdin);
	char t[n];
	fgets(t, n, stdin);
	char s_digits[n];
	char s_letters[n];
	int j=0;
	int j2=0;
	for(int i=0;i<strlen(s);i++)
		if(s[i]!=' ')
		{
			if(s[i]>='0' && s[i]<='9')
			{
				s_digits[j]=s[i];
				j++;
			}
			else
			{
				s_letters[j2]=s[i];
				j2++;
			}
		}
	int z=0;
	char ans[2*n];
	for(int i=0;i<strlen(s_digits);i++)
	{
		ans[i]=s_digits[i];
		z=i;
	}
	for(int i=0;i<strlen(t);i++)
	{
		ans[z+1]=t[i];
		z++;
	}
	for(int i=0;i<strlen(s_letters);i++)
	{
		ans[z]=s_letters[i];
		z++;
	}
	for(int i=0;i<strlen(ans);i++)
		printf("%c", ans[i]);
	return 0;
}
