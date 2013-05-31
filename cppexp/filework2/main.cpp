#include <fstream>
#include <iostream>
#include <string>
int main(int argc, char** argv)
{
    std::ifstream in("a.txt");
    float f;
    in >> f;
    std::cout<<f;
    std::string s;
    in >> s;
    std::cout<<s;
    in >> f;
    std::cout<<f;
    in.close();
    return 0;
}

