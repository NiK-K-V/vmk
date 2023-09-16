#include <stdio.h>

int main(void)
{
    float a;
    scanf("%f", &a);
    double n=1;
    do
    {
    a=a-1/n;
    n=n+1;
    }
    while (a>=0);
    n=n-1;
    int ans=(int)n;
    printf("%d \n", ans);
    return 0;
}
