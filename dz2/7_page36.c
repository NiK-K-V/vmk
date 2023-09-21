#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define n 100
int main(void)
{
	char s[n];
	fgets(s, n, stdin);
	char s2[n];
	fgets(s2, n, stdin);
	char new_s[n];
	char new_s2[n];
	int j=0;
	int j2=0;
	for(int i=0;i<strlen(s);i++)
		if(s[i]!=' ')
		{
			new_s[j]=s[i];
			j++;
		}
	for(int i=0;i<strlen(s2);i++)
		if(s2[i]!=' ')
		{
			new_s2[j2]=s2[i];
			j2++;
		}
	int z;
	if(strlen(new_s)>strlen(new_s2))
		z=strlen(new_s);
	else
		z=strlen(new_s2);
	int ans=1;
	for(int i=0;i<z;i++)
		if(new_s[i]!=new_s2[i])
			ans=0;
	if(ans==1)
		printf("yeeep \n");
	else
		printf("nope");
	return 0;
}
