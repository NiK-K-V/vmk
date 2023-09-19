#include <stdio.h>

int main(void)
{
    int n, test, x;
    int p=2;
    int check=0;
    scanf("%d", &n);
    do
    {
        test=1;
        x=0;
        do
        {
            if (p%test==0)
                x=x+1;
            test=test+1;
        }
        while (test<=p);
    if (x==2)
        {
            check=check+1;
            printf("%d \n", p);
        }
    p=p+1;
    }
    while (check<n);
    return 0;
}
