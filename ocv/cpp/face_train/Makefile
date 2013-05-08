#CC              := g++
CC              := clang++
CFLAGS          := `pkg-config --cflags opencv` -L/usr/lib --std=c++11
OBJECTS         := 
LIBRARIES       := `pkg-config --libs  opencv` #-lopencv_imgproc -lopencv_calib3d -lopencv_video -lopencv_features2d -lopencv_ml -lopencv_highgui -lopencv_objdetect -lopencv_contrib -lopencv_legacy #-I/usr/include/opencv  -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy 

#.PHONY: all clean

all: main 

main:  
	$(CC) $(CFLAGS) -o main main.cpp $(LIBRARIES)
	
clean:
	rm -f *.o main
