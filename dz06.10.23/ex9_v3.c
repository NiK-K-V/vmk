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
		if(z=='e' && z!=EOF)
		{
			z2=fgetc(f);
			if(z2=='n' && z2!=EOF)
			{
				z3=fgetc(f);
				if(z3=='d' && z3!=EOF)
				{
					fputc('}', f2);
				}
				else
				{
					fputc(z, f2);
					fseek(f, -2,SEEK_CUR);
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
			
		
		if(z=='b' && z!=EOF)
		{
			z2=fgetc(f);
			if(z2=='e' && z2!=EOF)
			{
				z3=fgetc(f);
				if(z3=='g' && z3!=EOF)
				{
					z4=fgetc(f);
					if(z4=='i' && z4!=EOF)
					{
						z5=fgetc(f);
						if(z5=='n' && z5!=EOF)
						{
							fputc('{', f2);
						}
						else
						{	
							fputc(z, f2);
							fseek(f, -4,SEEK_CUR);
						}
					}
					else
					{
						fputc(z, f2);
						fseek(f, -3,SEEK_CUR);
					}
				}
				else
				{
					fputc(z, f2);
					fseek(f, -2,SEEK_CUR);
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
			if(z!=EOF) 
			{
				fputc(z, f2);
			}
			else
			{
				break;
			}
		}

	}
					
	}
	fclose(f2);
	fclose(f);
	/*f = fopen("file3", "w");
	f2 = fopen("file4", "r"); 
	while(!feof(f2))
	{
		z=fgetc(f2);
		if(z!=EOF)
		{
			fputc(z, f);
		}
	}
	fclose(f2);
	fclose(f); */
	return 0; 
}
