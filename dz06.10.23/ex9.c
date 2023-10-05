#include <stdio.h>

int main(void) 
{ 
	FILE *f, *f2; 
	f= fopen("test02", "r+"); 
	f2 = fopen("test03", "w"); 
	//char str[100] = ""; 
	//char *estr; 
	int z, z2, z3, z4, z5;
	if(f == NULL) 
		printf("ERROR\n"); 
		
	
	while(feof(f)==0) 
	{ 
		z=fgetc(f);
		if((char)z=='e')
		{
			z2=fgetc(f);
			if((char)z2=='n')
			{
				z3=fgetc(f);
				if((char)z3=='d')
				{
					fputc('}', f2);
				}
				else
				{
					fputc(z, f2);
					fputc(z2, f2);
					fseek(f, -1,SEEK_CUR);
				}
			}
			else
			{
				fputc(z, f2);
				fseek(f, -1,SEEK_CUR);
			}
		}
		else
		{
			
		
		if((char)z=='b')
		{
			z2=fgetc(f);
			if((char)z2=='e')
			{
				z3=fgetc(f);
				if((char)z3=='g')
				{
					z4=fgetc(f);
					if((char)z4=='i')
					{
						z5=fgetc(f);
						if((char)z5=='n')
						{
							fputc('{', f2);
						}
						else
						{	
							fputc(z, f2);
							fputc(z2, f2);
							fputc(z3, f2);
							fputc(z4, f2);
							fseek(f, -1,SEEK_CUR);
						}
					}
					else
					{
						fputc(z, f2);
						fputc(z2, f2);
						fputc(z3, f2);
						fseek(f, -1,SEEK_CUR);
					}
				}
				else
				{
					fputc(z, f2);
					fputc(z2, f2);
					fseek(f, -1,SEEK_CUR);
				}
			}
			else
			{
				fputc(z, f2);
				fseek(f, -1,SEEK_CUR);
			}
		}
		else
		{
			fputc(z, f2);
		}
	}
					
	}
	//fputc(z, f2);
	//printf("%c \n", z);
		
	//} 
	fclose(f2);
	fclose(f); 
	return 0; 
}
