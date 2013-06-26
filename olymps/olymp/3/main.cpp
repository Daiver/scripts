#include <stdio.h>



int main()
{
    long N = 30, M = 3;
    long count = 0;
    while(M != N)
    {
        if(N < M)
        {
            long tmp = M;
            M = N;
            N = tmp;
        }
        count ++;// (N/M) - 1;
        N -= M;
    }
    printf("%ld\n", count);
    return 0;
}
