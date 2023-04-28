CC = gcc
CFLAGS = -ggdb3 -Wall

all: client server

client:
	$(CC) -o client -Wall -ggdb3 client.c -lrt

server:
	$(CC) -o server -Wall -ggdb3 server.c -lrt

clean:
	rm client server