CC = gcc
CFLAGS = -g -Wall -std=c11 -ggdb

static:
		$(CC) $(CFLAGS) -c library.c -o library.o
		ar rc library.a library.o

shared:
		$(CC) $(CFLAGS) -fPIC -c library.c -o library.o
		$(CC) $(CFLAGS) -shared -fPIC -o liblibrary.so library.o

clean:
		rm -rf *.o *.a *.so *.gch /tmp/tmp.txt main.dSYM main
