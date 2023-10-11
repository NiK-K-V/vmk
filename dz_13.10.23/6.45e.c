#include <stdio.h>
#include <stdlib.h>

typedef struct tnode tnode;

struct tnode 
{
	int elem;
	tnode *left;
	tnode *right;
};
	
tnode * add(tnode * p, int a)
{
	if (p==NULL) 
	{
		p=(tnode*)malloc(sizeof(tnode)); 
		p->elem=a;
		p->left=p->right=NULL;
	}
		else 
		{ 
			if (a < p->elem)  
			{ 
				p->left=add(p->left, a); 
			}
			else 
			{ 
				p->right=add(p->right, a); 
			} 
		}
		return p;
}

void treeprint(tnode *p)
{
	if (p!=NULL) 
	{
		treeprint(p->left);
		printf("%d\n", p->elem);
		treeprint(p->right);
	}
	else 
		return;
}

int count(tnode *p, int n)
	{
		int m=0;
		if (p==NULL && n>=0) 
		{
			return 0; 
		}
		else 
		{
			if (p!=NULL && n==0)
			{ 
				return 1; 
			}
			else 
			{
				 m+=count(p->left, n-1);
				 m+=count(p->right, n-1);
			}
		}
		return m;
	}

int main(void)
{
	tnode * tree = NULL;
	int x;
	tree = add(tree, 5);
	treeprint(tree);
	// 2 6 1 5 3
	for (int i=0; i<5; i++) 
	{
		scanf("%d", &x);
		tree = add(tree, x);
	} 
	treeprint(tree);
	printf("---\n");
	printf("Ans: %d\n", count(tree, 2));
	return 0;
}

