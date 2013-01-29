#include<iostream>
#include<stdio.h>
#include<fstream>

int f(int x)
{
    static int y = 0;
    y++;
    return x + y;
}

int main(int argc, char** argv)
{
    printf("Start...\n");
    for(int i = 0; i < 10; i++)
    {
        printf("%d: %d\n", i, f(1));
    }
    return 0;
}
