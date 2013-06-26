#include <stdio.h>
#include <math.h>

int main(int atgc, char** argv)
{
    long N = 123456;
    N = 16;
    for(long i = 1; i <= N/2; i ++)
        if (!(N % i))
            printf("i:%d %d\n", i, N / i);
    return 0;
}
