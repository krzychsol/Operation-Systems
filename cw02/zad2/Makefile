SHELL := /bin/bash
CC = gcc
CFLAGS = -g -Wall

all:
	make test BLOCK_SIZE=1
	make test BLOCK_SIZE=1024

test:
	$(CC) $(CFLAGS) reverse.c -o reverse_$(BLOCK_SIZE) -D BLOCK_SIZE=$(BLOCK_SIZE)

summary:
	make all
	
	rm -f pomiar_zad_2.txt pomiar_zad_2.txt

	i=1 ; while [[ $$i -le 5 ]] ; do \
		strings -s "" /dev/urandom | head -c 212120 > test.txt ; \
		./reverse_1 test.txt temp1.txt >> pomiar_zad_2.txt ; \
		./reverse_1024 test.txt temp1024.txt >> pomiar_zad_2.txt ; \
		((i = i + 1)); \
	done

	rm -f test.txt tmp_lib tmp_sys

clean:
		rm -rf *.o *.a *.so *.out reverse_* temp* test*
