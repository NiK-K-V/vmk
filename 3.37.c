#include <stdio.h>
#include <math.h>

int main(void)
{
    double eps=0.00001;
    int i=1;
    double cur, prev;
    do
    {
        prev=cur;
        cur=pow((1+1/(double)i), i);
        i=i+1;
    }
    while ((cur-prev)>=eps);
    printf("%f \n", cur);
    return 0;
}
