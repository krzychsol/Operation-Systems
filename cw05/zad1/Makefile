SHELL := /bin/bash
CC=gcc
CFLAGS=-Wall -O3

all: mail.c
	$(CC) $(CFLAGS) mail.c -o mail

report:
	make all
	i=1 ; while [[ $$i -le 10 ]] ; do \
		./mail test@wp.pl mailbomb "mailbomb_test"; \
		((i = i + 1)); \
	done
	echo "---------SORTED BY RECIPIENTS--------------" >> report.txt
	./mail nadawca >> report.txt
	echo "---------SORTED BY DATE--------------" >> report.txt
	./mail data >> report.txt

clean:
	rm -f mail *.txt