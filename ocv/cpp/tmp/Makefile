CC              := g++
#CC              := clang++
CFLAGS          := -I/usr/include/opencv2 -L/usr/lib
OBJECTS         := 
LIBRARIES       := `pkg-config --cflags --libs  opencv` #-lopencv_imgproc -lopencv_calib3d -lopencv_video -lopencv_features2d -lopencv_ml -lopencv_highgui -lopencv_objdetect -lopencv_contrib -lopencv_legacy #-I/usr/include/opencv  -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy 

.PHONY: all clean

all: test

test: 
	$(CC) $(CFLAGS) -o test test.cpp $(LIBRARIES)
	
clean:
	rm -f *.o
