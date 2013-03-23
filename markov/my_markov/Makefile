#CXX = clang++
CXX = g++

main: main.cc Matrix.o alg_impl.o HMM.o
	$(CXX) -o main main.cc Matrix.o HMM.o alg_impl.o

Matrix.o: Matrix.h Matrix.cpp
	$(CXX) -c -o Matrix.o Matrix.cpp

alg_impl.o: alg_impl.cpp alg_impl.h
	$(CXX) -c -o alg_impl.o alg_impl.cpp
	
HMM.o: HMM.cpp HMM.h alg_impl.o
	$(CXX) -c -o HMM.o HMM.cpp alg_impl.o
