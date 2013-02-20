clean: Account.o main test
	rm *.o

test: test.cc Account.h Account.o
	clang++ -o test main.cc Account.o

main: main.cc Account.h Account.o
	clang++ -o main main.cc Account.o

Account.o: Account.h Account.cpp
	clang -c Account.cpp -o Account.o
