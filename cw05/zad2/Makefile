SHELL := /bin/bash
CC=gcc
CFLAGS=-Wall -O3

all: integral.c
	$(CC) $(CFLAGS) integral.c -o integral

report:
	make all
	echo "" > report.txt
	./integral 0.000000001 1  >> report.txt
	./integral 0.000000001 5  >> report.txt
	./integral 0.0000000001 20 >> report.txt

clean:
	rm -f integral