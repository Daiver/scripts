CC              := g++
CFLAGS          := `pkg-config --cflags`
OBJECTS         := 
LIBRARIES       := `pkg-config --cflags --libs  opencv`

test: rect
	#$(CC) $(CFLAGS) -o test stereo_match.cpp $(LIBRARIES)
	$(CC) $(CFLAGS) -o test stereo_calib.cpp $(LIBRARIES)

rect: 
	$(CC) $(CFLAGS) -o rect rect.cpp $(LIBRARIES)
