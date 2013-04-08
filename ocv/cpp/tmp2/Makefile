CC              := g++
CFLAGS          := -I/usr/local/include/opencv -L/usr/local/lib
OBJECTS         := 
LIBRARIES       := -I/usr/include/opencv  -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy 

.PHONY: all clean

all: test

test: 
	$(CC) $(CFLAGS) -o test test.cpp $(LIBRARIES)
	
clean:
	rm -f *.o
