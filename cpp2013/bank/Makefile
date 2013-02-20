clean: Account.o main
	rm *.o

main: main.cc Account.h Account.o
	clang++ -o main main.cc Account.o

Account.o: Account.h Account.cpp
	clang -c Account.cpp -o Account.o
