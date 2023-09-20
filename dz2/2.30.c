#include <stdio.h>
int main(void)
{	//a
	printf("-----------a \n");
	printf("short: %lu \n", sizeof(short));
	printf("int: %lu \n", sizeof(int));
	printf("long: %lu \n", sizeof(long));
	printf("float: %lu \n", sizeof(float));
	printf("double: %lu \n", sizeof(double));
	printf("long double: %lu \n", sizeof(long double));
	
	//b
	printf("-------------b \n");
	char a=-1;
	unsigned char b=-1;
	if(a==b)
		printf("unsigned \n");
	else
		printf("signed \n");
	
	//с
	printf("-------------c \n");
	int test=1;
	unsigned int test2=1u;
	long test3=1l;
	unsigned long test4=1ul;
	long long test5=1ll;
	unsigned long long test6=1ull;
	int test7=013;
	int test8=0xB;
	
	printf("%u \n", test);
	printf("%u \n", test2);
	printf("%ld \n", test3);
	printf("%lu \n", test4);
	printf("%lld \n", test5);
	printf("%llu \n", test6);
	printf("%u \n", test7);
	printf("%u \n", test8);
	
	float test9=3.14f;
	long double test10=123456.123l;
	float test11=1.56e+12;
	printf("%f \n", test9);
	printf("%Lf \n", test10);
	printf("%f \n", test11);
	
	//d
	printf("-------------d \n");
	printf("0-9 - %d-%d \n", '0', '9');
	printf("a-z - %d-%d \n", 'a', 'z');
	printf("A-Z - %d-%d \n", 'A', 'Z');
	printf("' ' - %d \n", ' ');
	
	//e
	printf("-------------e \n");
	int is=0;
	printf("%d \n", is); //ругается на отсутствие инициализации и присваивает 0
	
	//f
	printf("-------------f \n");
	const int z=5;
	//z=7;                //ругается на попытку изменить константу
	printf("%d \n", z);
	
	//g
	printf("-------------g \n");
	int u=-7;
	int v;
	v=u%3;               //вроде выдаёт остаток от модуля с минусом
	printf("%d \n", v);
	
	//h
	printf("-------------h \n");
	int o=3;
	int oo=3;
	if((o==3) == oo>2)      // > имеет бОльший приоритет, чем ==
		printf("yes");
		
	
	return 0;
}
