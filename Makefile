CFLAGS=$(shell pkg-config python3 --cflags)
LDFLAGS=$(shell pkg-config python3 --libs)
STATIC_LDFLAGS=$(shell pkg-config python3 --libs --static)
STATIC_LDFLAGS+=-static  -lpthread -lm -lutil -lz -lexpat  -lz -ldl -lc

CC=gcc
all:	loader
loader:	loader.o main.o
	$(CC) -o loader main.o loader.o $(STATIC_LDFLAGS)  
loader.o: loader.c debug.h
	$(CC) -c -o loader.o loader.c  $(CFLAGS) -fPIC
main.o:	main.c lib.h
	$(CC) -c -o main.o main.c $(CFLAGS) -fPIC 
lib.h:	build.sh
	./build.sh lib

shared:	shared_loader
shared_loader:	loader.o main.o
	$(CC) -o loader main.o loader.o $(LDFLAGS)  

clean:
	rm loader main.o loader.o lib lib.h main.h lib.zip -rf 
