#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef  char (*testfunc)(unsigned long value, char *string, int radix);

char ultoa_by_sprintf(unsigned long value, char *string, int radix)
{
    sprintf(string, "%ld\0", value);
    return 0;
}

bool assert_func(testfunc foo, unsigned long value, int radix, const char *true_value)
{
    char *source = new char[36];
    foo(value, source, radix);
    printf(">%s\n", source);
    int res = strcmp(true_value, source);
    return 0 == res;
}

bool dec_test(testfunc foo, unsigned long num_of_iter)
{
    for (unsigned long i = 0; i < num_of_iter; i++)
    {
        char *ansewer = new char[36];
        ultoa_by_sprintf(i, ansewer, 10);
        if (!assert_func(foo, i, 10, ansewer))
            return false;
    }
    return true;
}

int main(int argc, char** argv)
{
    if (dec_test(ultoa_by_sprintf, 100))
        printf("TRUE");
    else
        printf("FALSE");
    return 0;
}
