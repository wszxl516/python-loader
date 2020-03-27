CFLAGS=$(shell python3-config --cflags)
LDFLAGS=$(shell python3-config --libs)
CC=gcc
all:	loader
loader:	loader.c
	$(CC) -o loader loader.c -g $(CFLAGS) $(LDFLAGS) -fPIC

clean:
	rm loader 
