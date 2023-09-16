#include <stdio.h>

int main(void)
{
    int n=102;
    int ans=0;
    int x, y, z, true_n;
    true_n=n;
    do
    {
        n=true_n;
        x=n%10;
        n=n/10;
        y=n%10;
        n=n/10;
        z=n%10;
        n=n/10;
        if(x!=y)
            if(x!=z)
            {
                ans=ans+1;
            }
        true_n=true_n+1;
    }
    while(true_n<=987);
    printf("%d \n", ans);
    return 0;
}
