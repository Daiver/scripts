#include <stdio.h>
#include <stdlib.h>

typedef  char (*testfunc)(unsigned long value, char *string, int radix);

void test_func(testfunc foo, unsigned long value, int radix, char *true_value)
{

}

int main(int argc, char** argv)
{
    printf("Hello\n");
    return 0;
}
