#include <stdio.h>
#include<stdlib.h>

typedef char Data;
typedef struct Node Node;

struct Node 
{
    Data * data;
    Node * next;
};

void print(Node * list);
void push(Node ** plist, Data * d);
Data pop(Node ** plist);
int is_empty(Node * list);

void push(Node ** plist, Data * d) //добавление элемента в конец списка
{
    Node * p = malloc(sizeof(Node));
	p->data = d;
	p->next = *plist;
	*plist = p;
}

void print(Node * list) //вывод списка
{
    for(Node * p = list; p != NULL; p = p->next){
        printf("%c ", (int) *(p->data));}
    printf("\n");
}

Data pop(Node ** plist) // удаление последнего элемента стека
{
    Node * p = *plist;
    Data res = *(p->data);   
    *plist = p->next;
    free(p);
    return res;
}

int is_empty(Node * list) //проверка на пустоту списка
{
    return list == NULL;
}

void push_to_3(Node ** plist, Node * list1, Node * list2) //добавление уникальных элементов из двух списков в новый
{
	Node * m = list1;
	Node * n;
	Node * p;
	Node * p2 = *plist;
	Data * c;
	int flag;
	while(m != NULL)
	{
		p2=*plist;
		n = list2;
		c = m->data;
		flag = 0;
		while(n != NULL)
		{
			if(*c == *(n->data))
			{
				flag = 1;
			}
			n=n->next;
		}
		while(p2 != NULL)
		{
			if(*c == *(p2->data))
			{
				flag = 1;
			}
			p2=p2->next;
		}
		if(flag == 0)
		{
			p = malloc(sizeof(Node));
			p->data = c;
			p->next = *plist;
			*plist = p;
		}
		m=m->next;
	}
	
	n=list2;
	while(n != NULL)
	{
		p2=*plist;
		m = list1;
		c = n->data;
		flag = 0;
		while(m != NULL)
		{
			if(*c == *(m->data))
			{
				flag = 1;
			}
			m=m->next;
		}
		while(p2 != NULL)
		{
			if(*c == *(p2->data))
			{
				flag = 1;
			}
			p2=p2->next;
		}
		if(flag == 0)
		{
			p = malloc(sizeof(Node));
			p->data = c;
			p->next = *plist;
			*plist = p;
		}
		n=n->next;
	}
}

int main()
{
    Data test[] = {'a', 'b', 'o', 'b', 'a'};
    Data test2[] = {'r', 'o', 'f', 'l'};
    Node * list = NULL;
    Node * list2 = NULL;
    Node * list3 = NULL;
    
    //printf("Empty: %s\n", is_empty(list) ? "YES": "NO");
    for(size_t i = 0; i < sizeof(test) / sizeof(test[0]); i++)
    {
        push(&list, &test[i]);
        //print(list);
    }
    for(size_t i = 0; i < sizeof(test2) / sizeof(test2[0]); i++)
    {
        push(&list2, &test2[i]);
        //print(list);
    }
    print(list);
    print(list2);
    push_to_3(&list3, list, list2);
    print(list3);
    //printf("Empty: %s\n", is_empty(list) ? "YES": "NO");
    
    return 0;
}
