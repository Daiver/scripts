#include <stdio.h>

class A
{
    public :
        virtual void f()
        {
            printf("A!");
        }
};

class B : public A
{
    public :
        void f()
        {
            printf("B!");
        }
};

int main(int argc, char** argv)
{
    A* p = new B();
    p->f();
}
