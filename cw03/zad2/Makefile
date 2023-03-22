CC = gcc
CFLAGS = -Wall

all: exec.c
		$(CC) $(CFLAGS) exec.c -o exec
		./exec ./empty_dir
		./exec . 
		./exec ~

clean:
		rm -f exec
