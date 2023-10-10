a) struct point create_point ( int a, int b) 
	{ struct point p; p.x=a; p.y=b; return p; }   -  можно
	
b) struct point ∗create_point ( int a, int b) 
	{ struct point p; p.x=a; p.y=b; return &p; }   - нельзя
	
c) struct point ∗create_point ( int a, int b) 
	{ struct point ∗pp; pp->x=a; pp->y=b; return pp; }  - нельзя
	
d) struct point ∗create_point ( int a, int b) 
	{ struct point ∗pp; pp = (struct point ∗) malloc(sizeof(struct point));
	pp->x=a; pp->y=b; return pp; }    - можно
