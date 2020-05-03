CFLAGS=$(shell pkg-config python3 --cflags)
LDFLAGS=$(shell pkg-config python3 --libs)
CFLAGS+=-g
STATIC_LDFLAGS=$(shell pkg-config python3 --libs)
STATIC_LDFLAGS+=-lpthread -lm -lutil -lz -lexpat  -lz -ldl -lc -static 

CC=gcc
all:	loader
loader:	loader.o main.o
	$(CC) -o loader main.o loader.o $(STATIC_LDFLAGS)  
loader.o: loader.c debug.h
	$(CC) -c -o loader.o loader.c  $(CFLAGS) -fPIC
main.o:	main.c lib.h config.h
	$(CC) -c -o main.o main.c $(CFLAGS) -fPIC 
lib.h:	build.sh
	./build.sh lib

shared:	loader.o main.o
	$(CC) -o loader_shared main.o loader.o $(LDFLAGS)  

clean:
	rm loader *.o lib lib.h main.h lib.zip -rf 
