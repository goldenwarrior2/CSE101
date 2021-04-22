CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

simulator: simulator.o Queue.o PriorityQueue.o
	$(CC) -o prog2 simulator.o Queue.o PriorityQueue.o -g

simulator.o: Queue.h Heap.h PriorityQueue.h simulator.c
	$(CC) -c simulator.c -g

Queue.o: Queue.h Queue.c
	$(CC) -c Queue.c -g

PriorityQueue.o: Heap.h PriorityQueue.h Heap.c PriorityQueue.c
	$(CC) -c PriorityQueue.c -g

clean:
	rm -f simulator simulator.o Queue.o Heap.o PriorityQueue.o prog2

check:
	valgrind --leak-check=full ./prog2 < test.txt
