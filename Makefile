CFLAGS=$(shell python3-config --cflags)
LDFLAGS=$(shell python3-config --libs)
CC=gcc
all:	loader
loader:	loader.o main.o
	$(CC) -o loader main.o loader.o $(LDFLAGS) 
loader.o: loader.c debug.h
	$(CC) -c -o loader.o loader.c  $(CFLAGS) -fPIC
main.o:	main.c
	$(CC) -c -o main.o main.c $(CFLAGS) -fPIC	

clean:
	rm loader main.o loader.o 
