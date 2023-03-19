# Zad3a - wykonane w 100%

CC = gcc
CFLAGS = -g -Wall 

static:
	$(CC) $(CFLAGS) -c ../zad1/library.c
	ar rcs library.a library.o
	$(CC) $(CFLAGS) -c ../zad2/main.c
	$(CC) main.o library.a -o main

shared:
	$(CC) $(CFLAGS) -fPIC -c ../zad1/library.c
	$(CC) -shared -o liblibrary.so library.o
	$(CC) $(CFLAGS) ../zad2/main.c -L. -llibrary -o main
	# Run with LD_LIBRARY_PATH=. ./main

dynamic:
	$(CC) $(CFLAGS) -fPIC -c ../zad1/library.c
	$(CC) -shared -o liblibrary.so library.o
	$(CC) $(CFLAGS) ../zad2/main.c -ldl -D DYNAMIC -o main
	# Run with LD_LIBRARY_PATH=. ./main

test_static:
	make static
	./main < test.txt > results_static.txt
	make clean

test_shared:
	make shared
	./main < test.txt > results_shared.txt
	make clean

test_dynamic:
	make dynamic
	./main < test.txt > results_dynamic.txt
	make clean

run_all:
	make test_static
	make test_shared
	make test_dynamic

clean:
	rm -rf *.so *.gch *.o *.a /tmp/tmp.txt main.dSYM main
