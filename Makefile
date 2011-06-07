
CC=gcc
CFLAGS=-g

btree.o: btree.c btree.h
	$(CC) $(CFLAGS) -c -o btree.o btree.c