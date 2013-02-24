#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void my_strncat(char *s, int n, const char *t)
{
    int oldlen = strlen(s);
    realloc(s, strlen(s) + n);
    for (int i = 0; i < n; i++) { s[oldlen + i] = t[i]; }
}

int main(int argc, char** argv)
{
    char *s = new char[4];
    strcpy(s, "hi1");
    char *t = "hi2";
    int n = 3;
    my_strncat(s, n, t);
    printf("%s\n", s);
    return 0;
}
