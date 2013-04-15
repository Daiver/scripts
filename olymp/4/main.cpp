#include <stdio.h>

int s_gcd(int a, int b)
{
    int c;
    while(b > 0)
    {
        c = a % b; a = b; b = c;  
    }
    return a;
}

int main()
{
    long A = 30, B = 3, D = s_gcd(A, B);

    printf("%ld\n", D);
    return 0;
}
