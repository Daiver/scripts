main: main.cpp main2 send recv
	g++ -o main main.cpp -lboost_system -lrt -lpython

main2: main2.cpp 
	g++ -o main2 main2.cpp -lboost_system -lrt

recv: recv.cpp 
	g++ -o recv recv.cpp -lboost_system -lrt

send: send.cpp 
	g++ -o send send.cpp -lboost_system -lrt
