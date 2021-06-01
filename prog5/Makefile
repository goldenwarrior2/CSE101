CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

da: da.o graph.o List.o
	$(CC) -o prog5 da.o graph.o List.o 

da.o: da.c
	$(CC) -c da.c

List.o: List.h List.c
	$(CC) -c List.c

graph.o: graph.h graph.c List.o
	$(CC) -c graph.c

clean:
	rm -f prog5 da da.o List.o graph.o

check: 
	valgrind --leak-check=full ./prog5
	
