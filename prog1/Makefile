CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c17

all: poly

poly: poly.o List.o
	$(CC) -o poly poly.o List.o

poly.o: List.h poly.c
	$(CC) -c poly.c

List.o: List.h List.c
	$(CC) -c List.c

clean:
	rm -f poly poly.o List.o

format:
	clang-format -style=file -i *.c *.h
