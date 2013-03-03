#include <boost/thread/thread.hpp>
#include <iostream>
#include <boost/bind.hpp>

void hello()
{
    std::cout <<
        "Hello world, I'm a thread!"
    << std::endl;
}

void hello2(int i)
{
    std::cout <<
        "Hello " << i
    << std::endl;
}

int main(int argc, char* argv[])
{
    boost::thread thrd(&hello);
    boost::thread thrd2(boost::bind(&hello2, 12));
    thrd.join();
    thrd2.join();
    return 0;
}
