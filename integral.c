#include <stdio.h>
#include <math.h>

double function(double x)
{
	double y = -x;
	return exp(y)/sqrt(x);
}

double integral(double a, double b, double n)    //метод трапеций
{
	double res;
	double h = (b - a) / n;
	res = (function(a) + function(b)) / 2;
	for(double i = a + h; i < b; i += h)
	{
		res += function(i);
	}
	res *= h;
	return res;
}

double integral2(double a, double b, double n)    //метод средних прямоугольников
{
	double res = 0;
	double h = (b - a) / n;
	for(double i = a; i < b; i += h)
	{
		res += function((i + (i + h)) / 2);
	}
	res *= h;
	return res;
}

int main(void)
{
	double ans = sqrt(M_PI) * (erf(sqrt(2)) - erf(1));     //аналитическое значение интеграла на [1,2] = sqrt(pi) * (erf(sqrt(2)) - erf(1)) 
	printf("%lf - аналитическое значение интеграла на [1,2]\n", ans);
	double ans2 = sqrt(M_PI) * erf(1);     //аналитическое значение интеграла на [0,1] = sqrt(pi) * erf(1) 
	printf("%lf - аналитическое значение интеграла на [0,1]\n", ans2);
	printf("---\n");
	printf("Метод Трапеций: \n");
	printf("Интервал (1, 2)\n");
	printf("%f  - разбиение на 16\n", integral(1, 2, 16));
	printf("%f  - разбиение на 32\n", integral(1, 2, 32));
	printf("%f  - разбиение на 64\n", integral(1, 2, 64));
	printf("---\n");
	printf("Интервал (0, 1)\n");
	printf("%f  - разбиение на 16\n", integral(0, 1, 16));
	printf("%f  - разбиение на 32\n", integral(0, 1, 32));
	printf("%f  - разбиение на 64\n", integral(0, 1, 64));
	printf("---\n");
	printf("Метод Средних Прямоугольников: \n");
	printf("Интервал (1, 2)\n");
	printf("%f  - разбиение на 16\n", integral2(1, 2, 16));
	printf("%f  - разбиение на 32\n", integral2(1, 2, 32));
	printf("%f  - разбиение на 64\n", integral2(1, 2, 64));
	printf("---\n");
	printf("Интервал (0, 1)\n");
	printf("%f  - разбиение на 16\n", integral2(0, 1, 16));
	printf("%f  - разбиение на 32\n", integral2(0, 1, 32));
	printf("%f  - разбиение на 64\n", integral2(0, 1, 64));
	printf("---\n");
	printf("%f  - разбиение на 256\n", integral2(0, 1, 256));
	printf("%f  - разбиение на 1024\n", integral2(0, 1, 1024));
	printf("%f  - разбиение на 2048\n", integral2(0, 1, 2048));
	printf("%f  - разбиение на 4096\n", integral2(0, 1, 4096));
	printf("%f  - разбиение на 8192\n", integral2(0, 1, 8192));
	printf("%f  - разбиение на 32768\n", integral2(0, 1, 32768));
	return 0;
}
