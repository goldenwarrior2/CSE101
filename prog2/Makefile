CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

simulator: simulator.o Queue.o PriorityQueue.o
	$(CC) -o prog2 simulator.o Queue.o PriorityQueue.o

simulator.o: Queue.h Heap.h PriorityQueue.h simulator.c
	$(CC) -c simulator.c

Queue.o: Queue.h Queue.c
	$(CC) -c Queue.c

PriorityQueue.o: Heap.h PriorityQueue.h Heap.c PriorityQueue.c
	$(CC) -c PriorityQueue.c

clean:
	rm -f simulator simulator.o Queue.o Heap.o PriorityQueue.o prog2

check:
	valgrind --leak-check=full ./prog2
