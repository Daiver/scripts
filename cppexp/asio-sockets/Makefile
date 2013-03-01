
clean: server client
	#rm *.o
	ls

server: server.cpp 
	g++ -o server server.cpp -lboost_system -lpthread

client: client.cpp
	g++ -o client client.cpp -lboost_system -lpthread
