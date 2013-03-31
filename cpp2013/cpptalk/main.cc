#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>

template<class A, class B>
auto sum(A a, B b) -> decltype(a + b)
{
    return a + b;
}

void autoTest()
{
    /*auto i = 10;
    std::cout<<i<<std::endl;
    i = 'A';
    std::cout<<i<<std::endl;
    i = new int [10];
    std::cout<<i<<std::endl;
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
    //for(auto it = vec.begin(); it != vec.end(); it++)
    {

        std::cout<<*it<<" ";
    }
    std::cout<<std::endl;
    */
    decltype(2 + 3.9) tmp;
    tmp = 10;
    printf("decl type test %f\n", tmp);
    std::cout<<"Sum test "<<sum(1.5, 2) <<std::endl;
    std::cout<<"Sum test2 "<<sum(1, 2.7) <<std::endl;
    printf("Sum test3 %d\n", sum(1, 2));
    printf("Sum test4 %f\n", sum(1, 2.5));
}

void forTest()
{
    std::vector<std::string> vec;
    vec.push_back("Love");
    vec.push_back("and");
    vec.push_back("Peace");
    for(std::string &s : vec)
    {
        std::cout<<s<<" ";
    }
    std::cout<<std::endl;

    for(auto &s : vec)
    {
        std::cout<<s<<" ";
    }
    std::cout<<std::endl;
}


int main(int argc, char** argv)
{
    autoTest();
    forTest();
    return 0;
}
