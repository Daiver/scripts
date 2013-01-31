main: main.cpp main2 send recv librecv.so.1.0
	g++ -o main main.cpp -lboost_system -lrt 

main2: main2.cpp 
	g++ -o main2 main2.cpp -lboost_system -lrt

recv: recv.cpp 
	g++ -o recv recv.cpp -lboost_system -lrt

send: send.cpp 
	g++ -o send send.cpp -lboost_system -lrt

librecv.so.1.0: librecv.o
	g++ -shared -o libtest.so.1.0 -lc librecv.o -L -lboost_system -lrt

librecv.o: librecv.cpp
	g++ -fPIC -c librecv.cpp  -lboost_system -lrt 

