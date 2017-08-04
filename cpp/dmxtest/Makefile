OBJS = main.o
CC = g++
DEBUG = -g
CFLAGS = -c $(DEBUG) -std=c++0x
LFLAGS = $(DEBUG) -lartnet -L/home/martin/libartnet/artnet/

dmxtest : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o dmxtest

main.o : src/main.cpp
	$(CC) $(CFLAGS) src/main.cpp

clean:
	\rm -v *.o dmxtest
