#include <utility>
#include <algorithm>
#include <stdio.h>

class A
{
public:
    int value;
    void move(A& a)
    {
        std::swap(this, &a);
    }
};

int main(int argc, char** argv )
{
    A a, b;
    a.value = 10; b.value = 13;
    a.move(b);
    printf("%d %d\n", a.value, b.value);
    return 0;
}
