#include <stdio.h>
#include <math.h>

int main(void)
{
    int a, b, c;
    double discr, root1, root2, v, w;
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);
    discr = b*b - 4*a*c;
    printf("Дискриминант = %f \n", discr);
    if (discr==0)
        {
            root1 = (-b)/(2*a);
            printf("1 корень - %f \n", root1);
        }
    if (discr>0)
        {
            discr=sqrt(discr);
            root1 = (-b+discr)/(2*a);
            root2 = (-b-discr)/(2*a);
            printf("2 корня - %f, ", root1);
            printf("%f \n", root2);
        }
    if (discr<0)
        {
            discr=-discr;
            discr=sqrt(discr);
            v=(-b)/(2*a);
            w=discr/(2*a);
            printf("2 корня - %f (±) ", v);
            printf("i*%f \n", w);
        }
    return 0;
}
