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
   if(argc == 1){ 
      struct shm_remove
      {
         shm_remove() { shared_memory_object::remove("MySharedMemory"); }
         ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
      } remover;

      managed_shared_memory segment(create_only, "MySharedMemory", 65536);

      const ShmemAllocator alloc_inst (segment.get_segment_manager());

      DataVector *myvector = segment.construct<DataVector>("MyVector")(alloc_inst);

      for(int i = 0; i < 100; ++i)  //Insert data in the vector
         myvector->push_back(i*10);

      std::string s(argv[0]); s += " child ";
      //if(0 != std::system(s.c_str()))
      //   return 1;

      //if(segment.find<DataVector>("MyVector").first)
      //   return 1;
      while(1)
      {
        sleep(100000);
      }
   }
/*   else{ 
      managed_shared_memory segment(open_only, "MySharedMemory");
      DataVector *myvector = segment.find<DataVector>("MyVector").first;
      std::sort(myvector->rbegin(), myvector->rend());
      for(int i = 0; i < 100; ++i)  //Insert data in the vector
      {
        printf("%f ", (float)myvector->at(i));
      }
      segment.destroy<DataVector>("MyVector");
   }*/

   return 0;
};
