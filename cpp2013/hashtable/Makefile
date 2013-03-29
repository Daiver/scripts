CXX = clang++
Options = -O3 -std=c++11
LIBS = -lpthread

main: main.cc hashtable.h test.o
	$(CXX) -o main main.cc test.o $(LIBS) $(Options)
	rm *.o

test.o: test.cpp
	$(CXX) -c -o test.o test.cpp $(Options)
