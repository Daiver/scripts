CXX = clang++
Options = -O3 
LIBS = -lpthread

main: main.cc hashtable.h test.o
	$(CXX) -o main main.cc test.o $(LIBS) $(Options)

test.o: test.cpp
	$(CXX) -c -o test.o test.cpp $(LIBS) $(Options)
