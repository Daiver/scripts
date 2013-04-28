#include<iostream>

class E
{
  public:
  E(){std::cout << "E ";}
};

class B : virtual E
{
  public:
    B():E(){std::cout<<"B ";}
};

class C: public E
{
  public:
    C():E(){std::cout<<"C ";}  
};
class D: virtual E
{
  public:
    D():E()
    {
        std::cout<<"D ";
    }
};

class A: virtual B, virtual C, public D
{
    public:
    A(): B(), C(), D()
    {
        std::cout<<"A ";
    }
};

int main()
{
  A *e = new A();
return 0;
}
