
// Совместная реализация Колтунов-Высочанская

#include <stdio.h>
#include <stdlib.h>

typedef int Data;
typedef struct Node Node;

struct Node // узел
{
    Data data;
    Node * prev;
    Node * next;
};

void print(Node * list);     // всё, что есть
void print_back(Node * list);
void print_dbg(Node * list);
void insert(Node * p, Node * t);
void insert_before(Node * q, Node * t);
void init(Node * list);
void list_remove(Node * t);
int is_empty(Node * list);
Node * push_front(Node * list, Data d);
Node * push_back(Node * list, Data d);
Data list_delete(Node * t);
Data pop_front(Node * list);
Data pop_back(Node * list);
void clear(Node * list);



void print(Node * list) //вывод списка
{
    for(Node * p = list->next; p != list; p = p->next){
        printf("%d ", p->data);}
    printf("\n");
}

void print_back(Node * list) //вывод списка в обратном порядке
{
    for(Node * p = list->prev; p != list; p = p->prev){
        printf("%d ", p->data);}
    printf("\n");
}

void print_dbg(Node * list) //вывод списка с адресами 
{
    Node * p = list;
    printf("---------\n");
    printf("list: prev = %p %p next = %p \n", p->prev, p, p->next);
    for(p = list->next; p != list; p = p->next)
        printf("%d prev = %p %p next = %p \n", p->data, p->prev, p, p->next);
}

void insert(Node * p, Node * t) // добавление элемента в произвольное место в списке после элемента p
{
    Node * q = p->next;//&b 
    t->prev = p;
    t->next = q;
    p->next = t;
    q->prev = t;
}

void insert_before(Node * q, Node * t) // добавление элемента в произвольное место в списке перед элементом p
{
    insert(q->prev, t);
}

void init(Node * list) //создание нулевого узла
{
    list->next = list;
    list->prev = list;
}

void list_remove(Node * t)
{
    Node * p = t->prev;
    Node * q = t->next;
    p->next = q;
    q->prev = p;
}

int is_empty(Node * list) //проверка на пустоту списка
{
    return list->prev == list && list->next == list;
}

Node * push_front(Node * list, Data d) // добавляет элемент в начало (динамическая память)
{
    Node * p = malloc(sizeof(Node)); 
    p->data = d;
    insert(list, p);
    return p;
}

Node * push_back(Node * list, Data d) // добавляет элемент в конец (динамическая память)
{
    push_front(list->prev, d);
    return 0;
}

Data list_delete(Node * t) // удаление узла
{
    list_remove(t);
    Data d = t->data;
    free(t);
    return d;
}

Data pop_front(Node * list) // удаление узла в начале
{
    return list_delete(list->next);
}

Data pop_back(Node * list) // удаление узла в конце
{
    return list_delete(list->prev);
}

void clear(Node * list) // удаление всего списка
{
    while(! is_empty(list))
        pop_front(list);
}

Node * search_push(Node * list, Data a, Data b)     // вставка после элемента с конкретным значением
{
    int flag = 0;
    Node * p;
    p = list->next;
    while(p != list)
    {
        if(p->data == a)
        {
            push_front(p, b);
            flag = 1;
            break;
        }
        p = p->next;
    }
    if(flag == 0)
        push_back(list, b);
    return 0;
}

void test_alloc()  //создание того же самого, но с динамической памятью
{
    Node z;
    Node * list = &z;
    
    Data test_data1[] = {21, 17, 3};
    Data test_data2[] = {10, 8};
    
    init(list);
    printf("Empty: %s\n", is_empty(list) ? "YES": "NO");
    
    Node * t;
    for(size_t i = 0; i < sizeof(test_data1) / sizeof(test_data1[0]); i++)
    {
        t = push_front(list, test_data1[i]);
        print(list);
        //printf("pushed: %d\n", t->data);
    }
    // 3 17 21
    for(size_t i = 0; i < sizeof(test_data2) / sizeof(test_data2[0]); i++)
    {
        t = push_back(list, test_data2[i]);
        print(list);
        //printf("pushed_back: %d\n", t->data);
    }
    // 3 17 21 10 8
    
    printf("Empty: %s\n", is_empty(list) ? "YES": "NO");
    
    /*t = list->next->next;    // 17
    Data res;
    
    res = list_delete(t);
    print(list);  // 3 21 10 8
    printf("deleted: %d\n", res);   
    
    res = pop_front(list);
    print(list);  // 21 10 8
    printf("pop front: %d\n", res); // 3
    
    res = pop_back(list);
    print(list);  // 21 10
    printf("pop front: %d\n", res); // 8
    
    clear(list);
    printf("Empty: %s\n", is_empty(list) ? "YES": "NO");*/
    
    print(list);
    search_push(list, 17, 7);
    print(list);
    search_push(list, 50, 33);
    print(list);
}


void test() // работа без динамической памяти
{
    Node z, a, b, c, u, w;
    Node * list = &z;
    z.data = 0;
    a.data = 3;
    b.data = 17;
    c.data = 21;
    u.data = 10;
    w.data = 8;

    init(list); 
    printf("Empty: %s\n", is_empty(list) ? "YES": "NO");
    
    insert(list, &c); 
    print(list);        // 21
    printf("Empty: %s\n", is_empty(list) ? "YES": "NO");
    
    insert(list, &b); 
    print(list);        // 17 21   
    
    insert(list, &a);
    print(list);        // 3 17 21

    print(list);        // 3 17 21
    print_back(list);   // 21 17 3 печать в обратном порядке
    print_dbg(list);    // 3 17 21
    
    insert(&a, &u); //после a вставляем u
    print(list);        // 3 10 17 21
    print_back(list);   // 21 17 10 3
    
    insert_before(&u, &w); 
    print(list);        // 3 8 10 17 21
    print_back(list);   // 21 17 10 8 3
    
    list_remove(&u);
    print(list);        // 3 8 17 21
    print_back(list);   // 21 17 8 3
    
    list_remove(&w);
    print(list);        //3 17 21
    print_back(list);   //21 17 3 
}

int main()
{
    
    //test();
    test_alloc();
    return 0;
}
