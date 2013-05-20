#include <iostream>
#include <vector>

int main (int argc, char** argv)
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    int *pi = nullptr;
    for(auto x : v)
    {
        std::cout<<x<<std::endl;
        if(nullptr != pi)
            std::cout<<*pi<<std::endl;
        else
            std::cout<<"NULL\n";
        if(x == 2) pi = &*x;
    }
    std::cout<<*pi;
    return 0;
}
