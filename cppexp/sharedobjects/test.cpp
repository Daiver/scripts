#include <stdio.h>
void _init()
{
    printf("Initialization of shared object\n");
}

// you can do final clean-up in this function
// it is called when the so is getting unloaded
void _fini()
{
    printf("Clean-up of shared object\n");
}

int add(int a, int b)
{
    return(a+b);
}
