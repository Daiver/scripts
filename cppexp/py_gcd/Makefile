CXX = clang++

libpygcd.so.1.0: libpygcd.o
	$(CXX) -shared -o libpygcd.so.1.0 -lc libpygcd.o -L -lboost_system -lrt -ldispatch -fblocks

libpygcd.o: libpygcd.cpp
	$(CXX) -fPIC -c libpygcd.cpp  -lboost_system -lrt -fblocks
