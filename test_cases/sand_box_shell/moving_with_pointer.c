#include <stdio.h>

void increase(int *i)
{
    *i = *i +1;
}

int main ()
{
    int i;
    
    i = 0;
    printf("before increment i = %d\n",  i);
    increase(&i);
    printf("after increment i = %d\n", i);
    
}
