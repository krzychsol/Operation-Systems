# Zad3b - Wykonano w 100%

CC = gcc
CFLAGS = -g -Wall

# O1

static_O1:
	$(CC) $(CFLAGS) -c ../zad1/library.c -O1
	ar rc library.a library.o
	$(CC) $(CFLAGS) -c ../zad2/main.c -O1
	$(CC) main.o library.a -o main

shared_O1:
	$(CC) $(CFLAGS) -fPIC -c ../zad1/library.c -O1
	$(CC) -shared -o liblibrary.so library.o
	$(CC) $(CFLAGS) ../zad2/main.c -L ./ -llibrary -o main -O1
	# Run with LD_LIBRARY_PATH=. ./main

dynamic_O1:
	$(CC) $(CFLAGS) -fPIC -c ../zad1/library.c -O1
	$(CC) -shared -o liblibrary.so library.o
	$(CC) $(CFLAGS) ../zad2/main.c -ldl -D DYNAMIC -o main -O1
	# Run with LD_LIBRARY_PATH=. ./main

test_static_O1:
	make static_O1
	./main < test.txt > results_static_O1.txt
	make clean

test_shared_O1:
	make shared_O1
	./main < test.txt > results_shared_O1.txt
	make clean

test_dynamic_O1:
	make dynamic_O1
	./main < test.txt > results_dynamic_O1.txt
	make clean

# O2

static_O2:
	$(CC) $(CFLAGS) -c ../zad1/library.c -O2
	ar rc library.a library.o
	$(CC) $(CFLAGS) -c ../zad2/main.c -O2
	$(CC) main.o library.a -o main

shared_O2:
	$(CC) $(CFLAGS) -fPIC -c ../zad1/library.c -O2
	$(CC) -shared -o liblibrary.so library.o
	$(CC) $(CFLAGS) ../zad2/main.c -L ./ -llibrary -o main -O2
	# Run with LD_LIBRARY_PATH=. ./main

dynamic_O2:
	$(CC) $(CFLAGS) -fPIC -c ../zad1/library.c -O2
	$(CC) -shared -o liblibrary.so library.o
	$(CC) $(CFLAGS) ../zad2/main.c -ldl -D DYNAMIC -o main -O2
	# Run with LD_LIBRARY_PATH=. ./main

test_static_O2:
	make static_O2
	./main < test.txt > results_static_O2.txt
	make clean

test_shared_O2:
	make shared_O2
	./main < test.txt > results_shared_O2.txt
	make clean

test_dynamic_O2:
	make dynamic_O2
	./main < test.txt > results_dynamic_O2.txt
	make clean

# O3

static_O3:
	$(CC) $(CFLAGS) -c ../zad1/library.c -O3
	ar rc library.a library.o
	$(CC) $(CFLAGS) -c ../zad2/main.c -O3
	$(CC) main.o library.a -o main

shared_O3:
	$(CC) $(CFLAGS) -fPIC -c ../zad1/library.c -O3
	$(CC) -shared -o liblibrary.so library.o
	$(CC) $(CFLAGS) ../zad2/main.c -L ./ -llibrary -o main -O3
	# Run with LD_LIBRARY_PATH=. ./main

dynamic_O3:
	$(CC) $(CFLAGS) -fPIC -c ../zad1/library.c -O3
	$(CC) -shared -o liblibrary.so library.o
	$(CC) $(CFLAGS) ../zad2/main.c -ldl -D DYNAMIC -o main -O3
	# Run with LD_LIBRARY_PATH=. ./main

test_static_O3:
	make static_O3
	./main < test.txt > results_static_O3.txt
	make clean

test_shared_O3:
	make shared_O3
	./main < test.txt > results_shared_O3.txt
	make clean

test_dynamic_O3:
	make dynamic_O3
	./main < test.txt > results_dynamic_O3.txt
	make clean

run_all:
	make test_static_O1
	make test_shared_O1
	make test_dynamic_O1
	make test_static_O2
	make test_shared_O2
	make test_dynamic_O2
	make test_static_O3
	make test_shared_O3
	make test_dynamic_O3

clean:
	rm -rf *.so *.o *.a /tmp/tmp.txt main.dSYM main