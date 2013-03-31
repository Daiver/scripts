#include <iostream>
#include <vector>
#include <stdio.h>

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
    std::cout<<"Sum test "<<sum(1.5, 2) <<std::endl;
    std::cout<<"Sum test2 "<<sum(1, 2.7) <<std::endl;
    int sum_res = sum(1, 2.5);
    printf("Sum test3 %d\n", sum(1, 2.5));
}

void forTest()
{
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    for(int &i : vec)
    {
        std::cout<<i<<" ";
    }
    std::cout<<std::endl;
}


int main(int argc, char** argv)
{
    autoTest();
    forTest();
    return 0;
}
