#include <stdio.h>
#include<stdlib.h>

typedef struct Node Node;
typedef struct Data Data;

struct Data
{
	double f;
	char *s[2];
};

struct Node 
{
    Data * data;
    Node * next;
};

void print(Node * list) //вывод списка
{
    for(Node * p = list; p != NULL; p = p->next){
        printf("%d-", (int) (*(p->data)).f);
        printf("%s ", *(*(p->data)).s);
    }
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

void l_copy(Node ** plist, Node * list1) //создание списка 2 - копии списка 1
{
	Node * m = list1;
	Node * p;
	while(m != NULL)
	{
		p = malloc(sizeof(Node));
		p->data = m->data;
		p->next = *plist;
		*plist = p;
		m=m->next;
	}
}

void l_reverse(Node ** plist, Node * list1) //если скучно и хочется, чтобы список выглядел также
{
	Node * m = list1;
	Node * p;
	while(m != NULL)
	{
		p = malloc(sizeof(Node));
		p->data = m->data;
		p->next = *plist;
		*plist = p;
		m=m->next;
	}
}

int main()
{
    Data test[] = { {1, {"ab"}},
					{2, {"cd"}},
					{3, {"ok"}}
					};
    Node * list = NULL;
    Node * list2 = NULL;
    Node * list3 = NULL;
    for(size_t i = 0; i < sizeof(test) / sizeof(test[0]); i++)
    {
        push(&list, &test[i]);
        //print(list);
    }
    print(list);
    l_copy(&list2, list);
    print(list2);
    l_reverse(&list3, list2);
    print(list3);
    return 0;
}
