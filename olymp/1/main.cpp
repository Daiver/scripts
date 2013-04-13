#include <stdio.h>

int gcd(int a, int b)
{
    int k = 0;
    if(a == 0) return b;
    while(b != 0)
    {
        //printf("a %d b %d\n", a, b);
        while(a != 0 && b != 0 && a % 2 == 0 && b % 2 == 0) 
        {
            k++; a /= 2; b /=2;
        }
       
        while(b % 2 == 0 && b != 0) b /= 2;
        while(a % 2 == 0 && a != 0) a /= 2;
        if (a < b)
        {
            int c = b;
            b = a;
            a = c;
        }
        //printf(">>a %d b %d\n", a, b);
        if(a == b)
        {
            break;
        }
        if(b == 1)
        {
            break;
        }
        a -= b;
    }
    if (a < b)
    {
        int c = b;
        b = a;
        a = b;
    }
    if (b == 1) 
    {
        for(int i = 0; i < k; i++) b *= 2;
        return b;
    }
    for(int i = 0; i < k; i++) a *= 2;
    return a;
}

int s_gcd(int a, int b)
{
    int c;
    while(b > 0)
    {
        c = a % b; a = b; b = c;  
    }
    return a;
}

int main(int argc, char **argv)
{
    //printf("%d \n", gcd(8, 98));
    //return 0;
    int a = 141, b = 180;
    for(int i = 0; i < 10000; i++)
        for(int j = 0; j < 10000; j++)
        {
            int res = gcd(i, j); int res2 = s_gcd(i, j);
            if(res != res2)
                printf("a %d b %d %d %d\n", i, j, res, res2);
        }
    return 0;
}
