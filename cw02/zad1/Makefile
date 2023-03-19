SHELL := /bin/bash
CC = gcc
CFLAGS = -g -Wall

all: 
	make lib
	make sys

lib: replace_letter.c
	$(CC) $(CFLAGS) replace_letter.c -o replace_letter_lib

sys: replace_letter.c
	$(CC) $(CFLAGS) replace_letter.c -o replace_letter_sys -D SYS

summary:
	make all
	
	rm -f pomiar_zad_1_lib.txt pomiar_zad_1_sys.txt

	i=1 ; while [[ $$i -le 5 ]] ; do \
		strings -s "" /dev/urandom | head -c 10240000 > test.txt ; \
		./replace_letter_sys a b test.txt tmp_sys.txt >> pomiar_zad_1_sys.txt ; \
		./replace_letter_lib a b test.txt tmp_lib.txt >> pomiar_zad_1_lib.txt ; \
		((i = i + 1)); \
	done

	rm -f test.txt tmp_lib tmp_sys

clean:
		rm -rf *.o *.a *.so *.out replace_letter_lib replace_letter_sys tmp_lib tmp_sys
