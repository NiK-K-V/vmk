a) 
struct point
{
	int x;
	int y;
}


struct point create_point ( int a, int b) 
	{ struct point p; p.x=a; p.y=b; return p; }
	
b) 
struct color_point
{
	int x;
	int y;
	char color[10];
}

struct color_point create_point ( int a, int b, char color[]) 
	{ struct color_point p; p.x=a; p.y=b; p.color=color[1; return p; }

c)
struct complex_number
{
	double complex x;   //используется библиотека <complex.h>
}

struct complex_number create_point (dounle complex a) 
	{ struct complex_point p; p.x=a; return p; }

d)
struct rational_number
{
	unsigned int nominator, denominator;
}

struct point create_point (unsigned int a, unsigned int b) 
	{ struct point p; p.nominator=a; p.denominator=b; return p; }
