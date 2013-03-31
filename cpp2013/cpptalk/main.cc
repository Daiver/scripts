#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <functional>

void autoTest();
void forTest();
void lambdaTest();

int main(int argc, char** argv)
{
    autoTest();
    //lambdaTest();
    //forTest();
    return 0;
}

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


void lambdaTest()
{
    std::vector<std::string> vec;
    vec.push_back("Be");
    vec.push_back("or");
    vec.push_back("not");
    vec.push_back("to");
    vec.push_back("be");
    
    std::for_each(vec.begin(), vec.end(), [](std::string s){
        std::cout<<s<<" ";
    });
    std::cout<<std::endl;
    
    char separator = '_';
    std::for_each(vec.begin(), vec.end(), [separator](std::string s){
        std::cout<<s<<separator;
    });
    std::cout<<std::endl;

    separator = '|';
    std::for_each(vec.begin(), vec.end(), [&separator](std::string s){
        std::cout<<s<<separator;
        separator = ' ';
    });
    std::cout<<std::endl;
    
    auto f1 = [](double a, double b) -> double
    {
        return a + b;
    };
    std::cout<<"f1 "<<f1(3, 2)<<std::endl;
    
    auto f2 = [f1](double a) -> double
    {
        return f1(a, 100);
    };
    
    std::cout<<"f2 "<<f2(3)<<std::endl;
    auto f3 = [](std::function<double(double)> f1, double a) -> double
    {
        return f1(a)*10;
    };
    std::cout<<"f3 "<<f3(f2, 3)<<std::endl;
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
    /*
    for(auto &s : vec)
    {
        std::cout<<s<<" ";
    }
    std::cout<<std::endl;*/
}

