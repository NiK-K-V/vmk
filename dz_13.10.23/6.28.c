#include <stdio.h>
#include<stdlib.h>

typedef double Data;
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

void print(Node * list) //вывод списка
{
    for(Node * p = list; p != NULL; p = p->next){
        printf("%d ", (int) *(p->data));}
    printf("\n");
}

void push(Node ** plist, Data * d) //добавление элемента в конец списка
{
    Node * p = malloc(sizeof(Node));
	p->data = d;
	p->next = *plist;
	*plist = p;
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

//  a) поменять местами первый и последний
void first_last(Node * list)
{
	Node * p = list;
	Data * x;
	if(p != NULL)
	{
		x=list->data;
		while(p->next != NULL)
		{
			p=p->next;
		}
		list->data=p->data;
		p->data=x;
	}
}

//  b) удаление первого вхождения
void delete_first(Node ** plist, Data x)
{
	Node * p = *plist;
	Node * p2 = p;
	int flag = 0;
	if(p != NULL)
	{
		while(p->next != NULL)
		{
			flag=0;
			if((*(p->next)->data) == x)
			{
				pop(&(p->next));
				//print(*plist);
				flag=1;
				break;
			}
			p2=p;
			if(p->next != NULL)
				p=p->next;
			if(flag != 0)
				p=p2;
		}
		if(flag == 0)
		{
			p=*plist;
			if(*(p->data) == x)
			{
				*plist=p->next;
				free(p);
			}
		}
	}
}

//  c) удаление всех вхождений
void delete_all(Node ** plist, Data x)
{
	Node * p = *plist;
	Node * p2 = p;
	int flag = 0;
	if(p != NULL)
	{
		while(p->next != NULL)
		{
			flag=0;
			if((*(p->next)->data) == x)
			{
				pop(&(p->next));
				//print(*plist);
				flag=1;
			}
			p2=p;
			if(p->next != NULL)
				p=p->next;
			if(flag != 0)
				p=p2;
		}
		p=*plist;
		if(*(p->data) == x)
		{
			*plist=p->next;
			free(p);
		}
	}
}

//  d) после каждого элемента с заданным значением, вставляет такой же элемент
void add(Node * p)
{
    Node * t = malloc(sizeof(Node)); 
    t->data = p->data;
    t->next = p->next;
    p->next = t;
}

void add_links(Node * list, Data x)
{
    Node * p = list;
    
    if(p != NULL)
    {
        while(p->next != NULL)
        {
            if(*(p->data) == x)
            {
                add(p);
                p = p->next;
            }
            p = p->next;
        }
        
        if((*(p->data) == x) && (p->next == NULL)) // последний член
        {
            add(p);
        }
    }
}

int main()
{
    Data test[] = {7, 7, 21, 7, 7, 17, 3, 7, 10, 7, 7};
    Node * list = NULL;

    printf("Empty: %s\n", is_empty(list) ? "YES": "NO");
    for(size_t i = 0; i < sizeof(test) / sizeof(test[0]); i++)
    {
        push(&list, &test[i]);
        print(list);
    }
    //first_last(list);
    //add_links(list, 7);
    printf("------- \n");
    print(list);
    delete_first(&list, 7);
    print(list);
    delete_all(&list, 7);
    print(list);
    printf("Empty: %s\n", is_empty(list) ? "YES": "NO");
    
    /*while(!is_empty(list)){
        pop(&list);
        print(list);
    }
    printf("Empty: %s\n", is_empty(list) ? "YES": "NO");
	*/
    return 0;
}
