CC = gcc -std=c11
CFLAGS = -Wall -Wextra -Werror
OUT = pqueue.dll

.DEFAULT_GOAL := all

pqueue.o: pqueue.c pqueue.h
	$(CC) $(CFLAGS) -c pqueue.c -I.

all: pqueue.o
	$(CC) -shared $(CFLAGS) -o $(OUT) pqueue.o
.PHONY: all

clean: 
	del *.o, $(OUT)
.PHONY: clean