clean: main Operation.o
	rm *.o

main: main.cc Operation.o BlockOperation.o
	clang++ main.cc -I /usr/local/include -L /usr/local/lib -ldispatch -fblocks -lBlocksRuntime Operation.o -o main

Operation.o: Operation.h Operation.cpp
	clang++ -o Operation.o -c Operation.cpp

BlockOperation.o: Operation.o BlockOperation.h BlockOperation.cpp
	clang++ -o BlockOperation.o -c BlockOperation.cpp Operation.o -fblocks -I /usr/local/include -L /usr/local/lib -ldispatch
