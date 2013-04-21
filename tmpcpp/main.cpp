#include <iostream>
#include <string.h>

char *reverse(const char *str)
{
    int N = strlen(str);
    char* res = new char [N + 1];
    int i = 0;
    while(i < N )
    {
        res[i] = str[N - i - 1];
        i++;
    }
    res[N] = '\0';
    return res;
}

int main(int argc, char** argv)
{
    std::cout<<reverse(reverse(reverse("RedruM")))<<std::endl;
    return 0;
}
