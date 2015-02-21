all:
	g++ test.cpp -I/usr/local/include/SDL2 -o test -lSDL2 -lGL -lGLEW -pedantic 
