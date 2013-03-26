#include <stdio.h>
#include <string>

#include "test.h"
#include "hashtable.h"


long someFunc(int i)
{
    return i;
}

int main(int argc, char** argv)
{
    HashTable<int, int, someFunc> ht;
    runAllTests();
    return 0;
}
