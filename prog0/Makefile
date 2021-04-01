cc = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c17

all: prog0

prog0: prog0.o
	$(CC) -o prog0 prog0.o

prog0.o: prog0.c
	$(CC) $(CFLAGS) -c prog0.c

clean: 
	rm -f prog0 prog0.o

format:
	clang-format -style=file -i *.c
