CXX = clang++

main: main.cc Matrix.o test
	$(CXX) -o main main.cc Matrix.o

Matrix.o: Matrix.h Matrix.cpp
	$(CXX) -c -o Matrix.o Matrix.cpp

test: test.cc Matrix.o
	$(CXX) -o test test.cc Matrix.o
