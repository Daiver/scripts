#CXX = clang++
CXX = g++

main: main.cc Matrix.o
	$(CXX) -o main main.cc Matrix.o

Matrix.o: Matrix.h Matrix.cpp
	$(CXX) -c -o Matrix.o Matrix.cpp
