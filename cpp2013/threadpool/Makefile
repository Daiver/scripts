clean: main Operation.o
	rm *.o

main: main.cc Operation.o BlockOperation.o FunctionOperation.o ThreadPool.o main.o
	ld -o main main.o ThreadPool.o FunctionOperation.o Operation.o -I /usr/include -L/usr/lib -ldispatch /usr/lib/libBlocksRuntime.so.0 
	# clang++ main.cc -I /usr/local/include -L /usr/local/lib -ldispatch -fblocks -lBlocksRuntime Operation.o FunctionOperation.o ThreadPool.o -o main 

main.o: main.cc Operation.o BlockOperation.o FunctionOperation.o ThreadPool.o
	clang++ -o main.o -c main.cc -fblocks

Operation.o: Operation.h Operation.cpp
	clang++ -o Operation.o -c Operation.cpp -ldispatch

BlockOperation.o: Operation.o BlockOperation.h BlockOperation.cpp
	clang++ -o BlockOperation.o -c BlockOperation.cpp Operation.o -fblocks -ldispatch -I /usr/local/include -L /usr/local/lib 

FunctionOperation.o: Operation.o FunctionOperation.h FunctionOperation.cpp
	clang++ -o FunctionOperation.o -c FunctionOperation.cpp Operation.o -fblocks -ldispatch

ThreadPool.o: Operation.o ThreadPool.h ThreadPool.cpp
	clang++ -o ThreadPool.o -c ThreadPool.cpp Operation.o -fblocks -I /usr/local/include -L /usr/local/lub -ldispatch
	
