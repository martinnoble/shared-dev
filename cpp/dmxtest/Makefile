OBJS = main.o
CC = g++
DEBUG = -g
CFLAGS = -c $(DEBUG) `pkg-config --cflags opencv` -std=c++0x
LFLAGS = $(DEBUG) -lglut -lGL -lGLU -lrt -lartnet -lportaudio -lsndfile `pkg-config --libs opencv sdl` -L/home/martin/libartnet/artnet/

dmxtest : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o dmxtest

main.o : src/main.cpp
	$(CC) $(CFLAGS) src/main.cpp

clean:
	\rm -v *.o dmxtest
