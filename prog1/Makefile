CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic 

all: prog1

prog1: prog1.o List.o
	$(CC) -o prog1 prog1.o List.o -g

prog1.o: List.h prog1.c
	$(CC) -c prog1.c -g

List.o: List.h List.c
	$(CC) -c List.c -g

clean:
	rm -f prog1 prog1.o List.o

format:
	clang-format -style=file -i *.c *.h
