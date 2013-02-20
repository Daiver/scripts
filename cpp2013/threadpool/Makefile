clean: main Operation.o
	rm *.o

main: main.cc Operation.o BlockOperation.o FunctionOperation.o ThreadPool.o
	clang++ main.cc -I /usr/local/include -L /usr/local/lib -ldispatch -fblocks -lBlocksRuntime Operation.o FunctionOperation.o ThreadPool.o -o main 

Operation.o: Operation.h Operation.cpp
	clang++ -o Operation.o -c Operation.cpp

BlockOperation.o: Operation.o BlockOperation.h BlockOperation.cpp
	clang++ -o BlockOperation.o -c BlockOperation.cpp Operation.o -fblocks -I /usr/local/include -L /usr/local/lib -ldispatch

FunctionOperation.o: Operation.o FunctionOperation.h FunctionOperation.cpp
	clang++ -o FunctionOperation.o -c FunctionOperation.cpp Operation.o -fblocks 

ThreadPool.o: Operation.o ThreadPool.h ThreadPool.cpp
	clang++ -o ThreadPool.o -c ThreadPool.cpp Operation.o -fblocks 
