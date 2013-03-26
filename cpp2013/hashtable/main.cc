#include <stdio.h>

#include "hashtable.h"

long someFunc(int i)
{
    return i;
}

int main(int argc, char** argv)
{
    HashTable<int, int, someFunc> ht;
    printf("and so on\n");
    return 0;
}
