#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

typedef  char (*testfunc)(unsigned long value, char *string, int radix);

char ultoa_by_me(unsigned long value, char *string, int radix)
{
    if ((radix < 2) || (radix > 36)) 
    {
        return 1;
    }
    
    char *now_char = string;
    const char *symbols = "0123456789abcdef";
    unsigned long cur_value = value;
    do 
    {
       *now_char = symbols[cur_value % radix];
       now_char++;
       cur_value /= radix;
    } while(cur_value);
    
    std::reverse(string, now_char);

    return 0;
}

char ultoa_by_sprintf(unsigned long value, char *string, int radix)
{
    sprintf(string, "%ld\0", value);
    return 0;
}

bool assert_func(testfunc foo, unsigned long value, int radix, const char *true_value)
{
    char *source = new char[36];
    foo(value, source, radix);
    printf(">%s %s\n", source, true_value);
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

void test_result(bool result, const char *test_name)
{
    if (result)
    {
        printf("Test '%s' passed!\n", test_name);
    }
    else
    {
        printf("Test '%s' failed!\n", test_name);
    }
}

int main(int argc, char** argv)
{
    test_result(dec_test(ultoa_by_me, 1000), "dec_test");
    return 0;
}
