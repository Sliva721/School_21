CC=gcc
CFLAGS=-Wall -Wextra -Werror
BUILD=../build/

all: graph

graph: mystack.o parser.o calculation.o draw.o graph.o
	$(CC) $(CFLAGS) mystack.o graph.o parser.o draw.o calculation.o -o $(BUILD)graph -lm
	rm -rf *.o

calculation.o: calculation.c calculation.h
	$(CC) $(CFLAGS)	calculation.c -c

draw.o:
	$(CC) $(CFLAGS)	draw.c -c

graph.o: graph.c
	$(CC) $(CFLAGS) graph.c -c

polish_notation.o: polish_notation.c
	$(CC) $(CFLAGS) polish_notation.c -c

parser.o: parser.c
	$(CC) $(CFLAGS) parser.c -c

mystack.o: mystack.c mystack.h
	$(CC) $(CFLAGS) mystack.c -c

clean:
	rm -rf *.o $(BUILD)graph

rebuild: clean all
