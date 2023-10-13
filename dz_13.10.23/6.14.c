#include <string.h>
//a) 
struct point
{
	int x;
	int y;
};


struct point create_point ( int a, int b) 
{ 
	struct point p; 
	p.x=a; 
	p.y=b; 
	return p; 
};
	
//b) 
struct color_point
{
	int x;
	int y;
	char color[10];
};

struct color_point create_cpoint ( int a, int b, char color[10]) 
{ 
	struct color_point p; 
	p.x=a; 
	p.y=b; 
	strcpy(p.color, color); 
	return p; 
};


//d)
struct rational_number
{
	unsigned int x;
	unsigned int y;
};

struct rational_number create_rnumber ( unsigned int a, unsigned int b) 
{ 
	struct rational_number p; 
	p.x=a; 
	p.y=b; 
	return p; 
};

//c)
struct complex_number
{
	struct rational_number x;
	struct rational_number y;
};

struct complex_number create_cnumber(unsigned int a, unsigned int b, unsigned int a2, unsigned int b2)
{
	struct complex_number p;
	p.x= create_rnumber(a,  b);
	p.y= create_rnumber(a2, b2);
	return p;
}

