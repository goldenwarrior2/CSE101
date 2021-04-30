CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

simulator: simulator.o HashTable.o List.o
	$(CC) -o hwk2 simulator.o HashTable.o List.o -g

simulator.o: simulator.c
	$(CC) -c simulator.c -g

HashTable.o: HashTable.c
	$(CC) -c HashTable.c -g

List.o: List.c
	$(CC) -c List.c -g

clean:
	rm -f simulator simulator.o HashTable.o List.o hwk2

check: 
	valgrind --leak-check=full ./hwk2

format: 
	clang-format -style=file -i *.c *.h

