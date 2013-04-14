CC              := g++
CFLAGS          := `pkg-config --cflags`
OBJECTS         := 
LIBRARIES       := `pkg-config --cflags --libs  opencv`

test: 
	#$(CC) $(CFLAGS) -o test stereo_match.cpp $(LIBRARIES)
	$(CC) $(CFLAGS) -o test stereo_calib.cpp $(LIBRARIES)
