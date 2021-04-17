CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

simulator: simulator.o Queue.o
	$(CC) -o hwk1 simulator.o Queue.o

simulator.o: Queue.h simulator.c 
	$(CC) -c simulator.c

Queue.o: Queue.h Queue.c
	$(CC) -c Queue.c

clean:
	rm -f simulator simulator.o Queue.o hwk1

check: 
	valgrind --leak-check=full ./hwk1

format: 
	clang-format -style=file -i *.c *.h
