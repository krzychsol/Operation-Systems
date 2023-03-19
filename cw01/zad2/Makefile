CC = gcc
CFLAGS = -g -Wall
LIB_DIR = ../zad1

static:
	$(CC) $(CFLAGS) -c $(LIB_DIR)/library.c
	ar rc library.a library.o
	$(CC) $(CFLAGS) -c main.c
	$(CC) main.o library.a -o main

shared:
	$(CC) $(CFLAGS) -fPIC -c $(LIB_DIR)/library.c
	$(CC) -shared -o liblibrary.so library.o
	$(CC) $(CFLAGS) main.c -L. -llibrary -o main
	# Run with LD_LIBRARY_PATH=. ./main

dynamic:
	$(CC) $(CFLAGS) -fPIC -c $(LIB_DIR)/library.c
	$(CC) -shared -o liblibrary.so library.o
	$(CC) $(CFLAGS) main.c -ldl -D DYNAMIC -o main
	# Run with LD_LIBRARY_PATH=. ./main

clean:
	rm -rf *.so *.o *.a /tmp/tmp.txt main.dSYM main