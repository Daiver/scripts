#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <errno.h>
#include <errno.h>
#include <limits.h>

typedef  char (*testfunc)(unsigned long value, char *string, int radix);
inline char ultoa_by_me(unsigned long value, char *string, int radix)
{
    if ((radix < 2) || (radix > 36)) 
    {
        return 1;
    }
    
    char *now_char = string;
    char  * const symbols  = "0123456789abcdefghijklmnopqrstuvwxyz";
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

template <unsigned long base> char ultoa_by_me_template(unsigned long value, char *string)
{
    return ultoa_by_me(value, string, base);
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
    //printf(">%s %s\n", source, true_value);
    int res = strcmp(true_value, source);
    delete[] source;
    return 0 == res;
}

bool dec_test(testfunc foo, unsigned long num_of_iter)
{
    for (unsigned long i = 0; i < num_of_iter; i++)
    {
        char ansewer[36];
        ultoa_by_sprintf(i, ansewer, 10);
        if (!assert_func(foo, i, 10, ansewer))
        {
            return false;
        }
    }
    return true;
}

bool template_test()
{
    char *source = new char[36];
    unsigned long value;
    value = 17;
    ultoa_by_me_template<16>(value, source);
    if (strcmp(source, "11") != 0) return false;
    delete [] source;
    return true;
}

bool hex_test(testfunc foo)
{
    if (!assert_func(foo, 16, 16, "10")) return false;
    if (!assert_func(foo, 15, 16, "f")) return false;
    if (!assert_func(foo, 8, 16, "8")) return false;
    if (!assert_func(foo, 255, 16, "ff")) return false;
    if (!assert_func(foo, 254, 16, "fe")) return false;
    if (!assert_func(foo, 1, 16, "1")) return false;
    if (!assert_func(foo, 17, 16, "11")) return false;
    return true;
}

bool bin_test(testfunc foo)
{
    if (!assert_func(foo, 4, 2, "100")) return false;
    if (!assert_func(foo, 6, 2, "110")) return false;
    if (!assert_func(foo, 16, 2, "10000")) return false;
    if (!assert_func(foo, 7, 2, "111")) return false;
    if (!assert_func(foo, 0, 2, "0")) return false;
    if (!assert_func(foo, 13, 2, "1101")) return false;
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
    const char* usage_message = "USAGE: ./main -t #runs tests \n\t ./main value base #runs function";
    if (argc <= 1)
    {
        printf("%s\n", usage_message);
    } else if (strcmp(argv[1], "-t") == 0)
    {
        printf("Start testes...\n");
        test_result(dec_test(ultoa_by_me, 10000), "dec_test");
        test_result(hex_test(ultoa_by_me), "hex_test");
        test_result(bin_test(ultoa_by_me), "bin_test");
        test_result(template_test(), "template_test");
    } else 
    {
        char *endline;
        //unsigned long value = atoi(argv[1]);
        long value = strtol(argv[1], &endline, 10);
        if ((endline == argv[1]) || (errno == ERANGE && (value == LONG_MAX || value == LONG_MIN)) || (value < 0))
        {
            printf("Wrong num");
            return 0;
        }

        char* source = new char[255];
        if (argc > 2)
        {
            //unsigned long base = atoi(argv[2]);
            long base = strtoul(argv[2], &endline, 10);

            if ((endline == argv[1]) || (errno == ERANGE && (base == LONG_MAX || base == LONG_MIN)) || (base < 0))
            {
                printf("Wrong num");
                return 0;
            }
            if(ultoa_by_me(value, source, base))
            {
                printf("Wrong base!\n");
                return 0;
            }
            printf(">%ld %ld >>> %s\n", value, base, source);
        }
        else
        {
            ultoa_by_me_template<16>(value, source);
            printf(">%ld 16 >>> %s\n", value, source);
        }
        delete[] source;
    }     
    return 0;
}
