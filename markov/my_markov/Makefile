#CXX = clang++
CXX = g++

main: main.cc Matrix.o alg_impl.o
	$(CXX) -o main main.cc Matrix.o alg_impl.o

Matrix.o: Matrix.h Matrix.cpp
	$(CXX) -c -o Matrix.o Matrix.cpp

alg_impl.o: alg_impl.cpp alg_impl.h
	$(CXX) -c -o alg_impl.o alg_impl.cpp
	
