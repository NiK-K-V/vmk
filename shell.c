#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#define N 7

typedef char * Data;

enum type_of_next
{
    NXT, 
    AND, 
    OR   
};



typedef struct tree_node tree_node;
struct tree_node 
{
	int argc;                           // количество аргументов
	char **argv;                        // список из имени команды и аргументов
	char *infile;                       // переназначенный файл стандартного ввод
    char *outfile;                      // переназначенный файл стандартного вывода
    int append;                         // дозапись в файл
    int backgrnd;                       // = 1, если команда подлежит выполнению в фоновом режиме
	tree_node *psubcmd;            		// команды для запуска в дочернем shell
    tree_node *pipe;               		// следующая команда после "|"
    tree_node *next;               		// следующая после ";" (или после "&")
    enum type_of_next type;             // связь со следующей командой через ; или && или ||
};

tree_node * rewind_pipe_subshell(tree_node *root);

int run_shell_or_subshell(tree_node *root);

int tree_handler(tree_node *root);

typedef struct Node Node;   //всё в односвязном списке
struct Node
{
    char* word;
    Node* next;
};

Node* push(Node* plist, char* w)   //пуш в список
{
	Node* list = plist;
    Node* p = calloc(1, sizeof(Node));
    p -> word = w;
    p -> next = NULL;
    if (plist == NULL)
    	list = p;
    else
    {
    	while (plist -> next != NULL)
    		plist = plist -> next;
    	plist -> next = p;
    }
    return list;
}

void print(Node* list)   //печать списка
{
	if (list != NULL)
	{
		if (list -> word != NULL)
			printf("%s ", list -> word);
		if (list -> next != NULL)
		{
			printf(", ");
			print(list -> next);
		}
	}
}

int is_empty(Node * list) 
{
    return list == NULL;
}

Data pop(Node **plist)
{
    Node *p = *plist;
    Data res = p->word;
    *plist = p->next;

    free(p);
    return res;
}  

void delete_list(Node **plist)
{
    while (!is_empty(*plist))
    {
        free(pop(plist));
    }
}

void pass(char* word, int* j, Node** list)   //для обычных слов/команд
{
	word[*j] = '\0';  *j = 0;  //в обычной строке у нас \0 по умолчанию в конце, а тут надо самим
	if (strlen(word) != 0)
	{
		char* w;
		w = calloc(strlen(word) + 1, 1);   // +1 для \0
		strcpy(w, word);
		*list = push(*list, w);
	}
}

void pass1(char op, Node** list)   //для одинарных спецсимволов
{
	char* w;
	w = calloc(2, 1);
	w[0] = op; 
	w[1] = '\0';
	*list = push(*list, w);
}

void pass2(char op, Node** list)   //для двойных || >> &&
{
	char* w;
	w = calloc(3, 1);
	w[0] = op; 
	w[1] = op;
	w[2] = '\0';
	*list = push(*list, w);
}

Node * string_parse(void)     //парсинг работает ура
{
	Node* list = NULL;
    char buf[N + 1];    //и снова для \0
    char op;
    int size = N;

    int i, j = 0;
    int split = 0, ln = 0;
    int quotes = 0;

    char* word = calloc(N, 1);

    while (fgets(buf, N + 1, stdin) != NULL)
    {
    	i = 0;
    	if (split) //двойной символ разделен(split) между порциями
    	{
    		if (buf[i] == op)
    		{
    			pass2(op, &list);
				i++;
    		}
    		else
    			pass1(op, &list);
    		split = 0;
    	}
    	for (; i < N; ++i)
    	{
    		if (quotes && (buf[i] != '"')) //кавычки
    		{
				if(buf[i] == '\n')   //нажали enter с одной кавычкой
				{
					printf("%s", "\033[01;36m");
					printf("Введите закрывающую кавычку > ");
					printf("%s", "\033[0m");
				}
				if(buf[i] != '\n')
				{
					word[j] = buf[i]; 
					j++;
				}
    			continue;
    		}
			switch (buf[i])
			{
				case '"':
				{
					pass(word, &j, &list);
					quotes = !quotes;
					break;
				}
				case ' ': case '\t':   //пробелы и табуляция
				{
					pass(word, &j, &list);
					break;
				}
				case '\n':    //enter
				{
					pass(word, &j, &list);
					ln = 1;
					break;
				}
				case ';': case '<': case '(': case ')':   //всегда одинарные спецсимволы
				{
					pass(word, &j, &list);
					pass1(buf[i], &list);
					break;
				}
				case '|': case '&': case '>':   //одинарные/двойные спецсимволы
				{
					pass(word, &j, &list);
					op = buf[i];
					if (i == N - 1) //в конце порции?  (возможно разбилось пополам)
						split = 1;
					else
					{
						if (buf[i + 1] == op)
						{
							pass2(op, &list);
							i++;
						}
						else
							pass1(op, &list);
					}
					break;
				}
				default: //обычная строка
				{
					word[j] = buf[i]; 
					j++;
				}

			}
    		if(ln)    //новая строка - печатаем list
    		{	
				ln = 0;
				free(word);
    			return(list);
    		    //del(&list);
    		}
    	}

    	if (j == size)
    	{
    		word = realloc(word, size + N);    //добавляем память
    		size += N;
    	}
    }

    free(word);
    return(list);
}

tree_node * tree_create(void)     //инициализация дерева этой адской структуры
{
    tree_node *root = calloc(1, sizeof(tree_node));   //корень
    root->argc = 0;
    root->argv = calloc(1, sizeof(char *));
    root->infile = NULL;
    root->outfile = NULL;
    root->append = 0;
    root->backgrnd = 0;
    root->psubcmd = NULL;
    root->pipe = NULL;
    root->type = NXT;
    
    return root;
}

void tree_delete(tree_node *root)     //удаление дерева
{
    if (root == NULL)
    {
        return;
    }
    tree_delete(root->psubcmd);
    tree_delete(root->pipe);
    tree_delete(root->next);
	for (int i = 0; root->argv[i] != NULL; i++)
    {
        free(root->argv[i]);
    }
	free(root->argv);
    free(root);
}

void tree_print(tree_node *root)       //печать дерева
{
    if (root == NULL)
        return;
    printf("\n");
    printf("argc: %d\n", root->argc);
    for (int i = 0; (root->argv[i]) != NULL; i++)
    {
        printf("argv %d: %s\n", i, root->argv[i]);
    }
    printf("infile: %s\n", root->infile);
    printf("outfile: %s\n", root->outfile);
    printf("append: %d\n", root->append);
    printf("background: %d\n", root->backgrnd);
    printf("next cmd type: %d\n", root->type);
	if (root->psubcmd)
    {
        printf("exist psubcmd %s\n", root->psubcmd->argv[0]);
    }
    if (root->pipe)
    {
        printf("exist pipe %s\n", root->pipe->argv[0]);
    }
    if (root->next)
    {
        printf("exist next %s\n", root->next->argv[0]);
    }
	tree_print(root->psubcmd);      
    tree_print(root->pipe);        
    tree_print(root->next);        
}

int is_op(Node *list)     //операнд
{
    if ((!strcmp(list->word, ">")) || (!strcmp(list->word, ">>")) || (!strcmp(list->word, "&")) || (!strcmp(list->word, "|")) ||
        (!strcmp(list->word, "\"")) || (!strcmp(list->word, "<")) || (!strcmp(list->word, "(")) || (!strcmp(list->word, ")")) ||
        (!strcmp(list->word, "||")) || (!strcmp(list->word, "&&")))
        return 0; 
    return 1;
}

void add_argv(tree_node *root, char *arg)    //добавление аргументов
{
    int num = ++root->argc;
    root->argv = realloc(root->argv, (num + 1) * sizeof(char *));
    root->argv[num - 1] = arg;
    root->argv[num] = NULL;
}

tree_node * build_tree(Node *list)    //построение
{
    Node *p = list;
    tree_node *root = tree_create();
	int tree_finished = 0;

    for (; p != NULL; p = p->next)
    {
        if (!strcmp(p->word, ">"))
        {
            if(root->outfile != NULL)
            {
                printf("Error: two output files\n");     //получили >, но в графе outfile уже что-то записано
                tree_delete(root);
                return NULL;
            }
			root->outfile = p->next->word;
            p = p->next;
        }
        else if (!strcmp(p->word, ">>"))      //получили >>, но в графе outfile уже что-то записано
        {
            if(root->outfile != NULL)
            {
                printf("Error: two output files\n");
                tree_delete(root);
                return NULL;
            }
			root->outfile = p->next->word;
            root->append = 1;      //флаг дозаписи в файл, так как получили >>
            p = p->next;
        }
        else if (!strcmp(p->word, "<"))
        {
            if(root->infile != NULL)
            {
                printf("Error: two input files\n");     //получили <, но в графе infile уже что-то записано
                tree_delete(root);
                return NULL;
            }
			root->infile = p->next->word;
            p = p->next;
        }
        else if (!strcmp(p->word, ";"))
        {
            root->type = NXT;
            root->next = build_tree(p->next);
            break;
        }
        else if (!strcmp(p->word, "&&"))
        {
            root->type = AND;
            root->next = build_tree(p->next);
            break;
        }
        else if (!strcmp(p->word, "||"))
        {
            root->type = OR;
            root->next = build_tree(p->next);
            break;
        }
        else if (!strcmp(p->word, "&"))
        {
            root->backgrnd = 1;
            root->next = build_tree(p->next);
            break;
        }
        else if (!strcmp(p->word, "|"))
        {
            root->pipe = build_tree(p->next);
            break;
        }
        else
        {
            char *arg = calloc(1, strlen(p->word) + 1);
            strcpy(arg, p->word);
            add_argv(root, arg);
        }
        tree_finished = 1;
    }

    if(!tree_finished)
    {
        tree_delete(root);
        return NULL;
    }
    else
    {
        return root;
    }
}

int set_input_output(tree_node *root)         //по названию понятно
{
    int fd;
    if (root->infile != NULL)       //<
    {
        if((fd = open(root->infile, O_RDONLY)) == -1)
        {
            fprintf(stderr, "Error in opening file: %s\n", strerror(errno));      //stderr - поток для ошибок, когда-то проходили
            return 1;																//strerror возвращает строку, описывающую ошибку
        }
        if (dup2(fd, 0) == -1)    //создаёт копию файлового дескриптора
        {
            fprintf(stderr, "Error in dup2: %s\n", strerror(errno));
            return 1;
        }
    }

    if (root->outfile != NULL)
    {
        if (root->append)        // >>
        {
            if((fd = open(root->outfile, O_WRONLY | O_CREAT | O_APPEND, 0666)) == -1)
            {
                fprintf(stderr, "Error in opening file: %s\n", strerror(errno));
                return 1;
            }
        }
        else                   // >
        {
            if((fd = open(root->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
            {
                fprintf(stderr, "Error in opening file: %s\n", strerror(errno));
                return 1;
            }
        }
        
        if (dup2(fd, 1) == -1)
        {
            fprintf(stderr, "Error in dup2: %s\n", strerror(errno));
            return 1;
        }
    }
    return 0;
}

tree_node * rewind_pipe_subshell(tree_node *root) 
{
    //if ((root->pipe == NULL) && (root->psubcmd == NULL))
        //return root;
    if(root->pipe != NULL)
        return rewind_pipe_subshell(root->pipe);
	if(root->psubcmd != NULL)
        return rewind_pipe_subshell(root->psubcmd);
    return root;      
}

int run_shell_or_subshell(tree_node *root)       //запускает команды
{
    int returned_value = 0;
    
    returned_value = tree_handler(root->psubcmd);
    if (execvp(root->argv[0], root->argv) == -1)
    {
		return -1;
    }
    return returned_value;
}

//в цикле обрабатывает пайп от начала до конца
int pipe_handler(tree_node *root) 
{    
    pid_t pid;
    int status;
    int fd[2];

    while (root != NULL) 
    {
        pipe(fd);
        pid = fork();
        
        if (pid == 0) 
        {
            signal(SIGINT, SIG_DFL);

            set_input_output(root);

            if (root->pipe != NULL) {
                dup2(fd[1], 1);      //перенаправляет вывод
            }
            close(fd[1]);
            close(fd[0]);

            if (run_shell_or_subshell(root) == -1)
            {
				exit(0);
                return -1;
            }
			exit(0);
        }
        dup2(fd[0], 0);       //перенаправляет ввод
        close(fd[1]);
        close(fd[0]);

        root = root->pipe;
    }

    while (wait(&status) > 0); 
    return status;
}


int tree_handler(tree_node *root) 
{
    if (root == NULL)
        return 0;

    int status = 0;

    if ((root->argv[0] != NULL) && (strcmp(root->argv[0], "cd") == 0)) //обработка cd
    {
        chdir(root->argv[1]);      //функция chdir() устанавливает в качестве текущего каталог, на который указывает параметр path
        status = tree_handler(root->psubcmd);

        if (root->next != NULL)
        {
            if ((root->type == NXT) || ((root->type == AND) && (status == 0)) ||
                ((root->type == OR) && (status != 0)))
					status = tree_handler(root->next);
        }
            
        return status;
    }

    //pipe
    if (root->pipe != NULL) 
    {
        status = pipe_handler(root);
        root = rewind_pipe_subshell(root);

        if (root == NULL)
            return status;

        if (root->next != NULL)
            if ((root->type == NXT) ||
                ((root->type == AND) && (status == 0)) ||
                ((root->type == OR) && (status != 0)))
					status = tree_handler(root->next);

        return status;
    }

    //сын
    if (fork() == 0) 
    {
        set_input_output(root);

        //фон
        if (root->backgrnd == 1) 
        {
            signal(SIGINT, SIG_IGN);
            
            if (fork() == 0) //внук
            {
                run_shell_or_subshell(root);     //сын-внук для реализации работы в фоновом режиме, создаётся внук, и сын убивает себя
                exit(0);
			} 
            else
            {
                //убийство отца
                kill(getpid(), SIGKILL);
			}

            //не фон
        } 
        else 
        {
            status = run_shell_or_subshell(root);
            if (status != 0)
                exit(1);
            else
                exit(0);
        }

      
    } 
    else //отец
    {
        wait(&status);
        status = WEXITSTATUS(status);

        if (root->next != NULL)
        {
            if ((root->type == NXT) ||
                ((root->type == AND) && (status == 0)) ||
				((root->type == OR) && (status != 0)))
					status = tree_handler(root->next);
        }
        return status;
    }
    return status;
}

int run_cmd(Node *list)
{
    int err = 0;
    tree_node *root = NULL;
    
    root = build_tree(list);
	err = tree_handler(root);
	if (err == 1)
        printf("my_shell: incorrect command\n");
    tree_delete(root);
    delete_list(&list);
    return err;
}

int get_len(Node *list)   //используем, когда ввели одну команду и это exit или q
{
    int size = 0;
	for(Node *p = list ; p!=NULL ; p = p->next)
    {
        ++size;
    }
    return size;
}

void invitation(void) 
{
    char s[PATH_MAX];
    getcwd(s, PATH_MAX);
    printf("%s", "\033[01;36m");
    printf("%s", s);
    printf(" > ");
    printf("%s", "\033[0m");   
}

int main(int argc, char *argv[])
{
	signal(SIGINT, SIG_IGN);  //игнорим ctrl+c
	Node *list = NULL;
	while (!feof(stdin))
    {
        int stdin_copy = dup(0);
		invitation();
        list = string_parse();
        //print(list);
		if ((get_len(list) == 1) && ((!strcmp(list->word, "q")) || (!strcmp(list->word, "exit")) || (!strcmp(list->word, "egorkreed")))) //завершение работы shell
        {
            delete_list(&list);
            break;
        }
        else
        {
            run_cmd(list);
        }
        close(0);
        dup2(stdin_copy, 0);
    }
    return 0;
}
