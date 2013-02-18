#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <iostream>

#include <sstream>

typedef  char (*testfunc)(unsigned long value, char *string, int radix);

char ultoa_by_sprintf(unsigned long value, char *string, int radix)
{
    sprintf(string, "%ld\0", value);
    return 0;
}

void assert_func(testfunc foo, unsigned long value, int radix, const char *true_value)
{
    char *source = new char[36];
    foo(value, source, radix);
    printf(">%s\n", source);
}

int main(int argc, char** argv)
{
    assert_func(ultoa_by_sprintf, 12, 10, "");
    return 0;
}
