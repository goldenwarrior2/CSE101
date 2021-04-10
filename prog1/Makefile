CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic 

all: poly

poly: poly.o List.o
	$(CC) -o poly poly.o List.o -g

poly.o: List.h poly.c
	$(CC) -c poly.c -g

List.o: List.h List.c
	$(CC) -c List.c -g

clean:
	rm -f poly poly.o List.o

format:
	clang-format -style=file -i *.c *.h
