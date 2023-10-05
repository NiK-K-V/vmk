#include <stdio.h>

int main(void) 
{ 
	FILE *f, *f2; 
	f = fopen("file3", "r+"); 
	f2 = fopen("file4", "w+"); 
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
			//fseek(f, -1,SEEK_CUR);
		}
	}
					
	}
	fclose(f2);
	fclose(f);
	f = fopen("file3", "w");
	f2 = fopen("file4", "r"); 
	while(!feof(f2))
	{
		z=fgetc(f2);
		fputc(z, f);
	}
	fclose(f2);
	fclose(f);
	return 0; 
}
