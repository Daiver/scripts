#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <string>
#include<stdio.h>
#include <cstdlib> //std::system

using namespace boost::interprocess;
typedef allocator<float, managed_shared_memory::segment_manager>  ShmemAllocator;
typedef vector<float, ShmemAllocator> DataVector;
int main(int argc, char *argv[])
{
      printf("Start...\n");
      managed_shared_memory segment(open_only, "MySharedMemory");
      printf("Start...\n");
      DataVector *myvector = segment.find<DataVector>("MyVector").first;
      printf("Start...\n");
      //std::sort(myvector->rbegin(), myvector->rend());
      for(int i = 0; i < 100; ++i)  //Insert data in the vector
      {
        printf("%f ", (float)myvector->at(i));
      }
      //segment.destroy<DataVector>("MyVector");

   return 0;
};
