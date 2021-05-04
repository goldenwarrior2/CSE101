#  Makefile for prog3
#  make			makes enrollment
#  make clean		removes object files
#  make check		runs valgrind to check for memory errors
#
#  Enrollment.h		This defines some application specific structs. You can modify this as needed.
#  Enrollment.c		This is the application code that you have to write.
#
#  HashTable.h		Given. Don't touch this.
#  HashTable.c		This is where you implement HashTable functions listed in HashTable.h
#  List.c 		List implementation. Comes from your hwk
#  List.h		List header file. Provided
#  Dictionary.h		Given. Don't touch this. The enrollment application will include this.
#  Dictionary.c		This is where you implement Dictionary functions listed in Dictionary.h
#----------------------------------------------------------------------------------------------
CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

Enrollment:	Enrollment.o HashTable.o Dictionary.o List.o
	$(CC) -o prog3 Enrollment.o HashTable.o Dictionary.o List.o -g

Enrollment.o:	Enrollment.h Enrollment.c
	$(CC) -c Enrollment.c -g

HashTable.o:	HashTable.h HashTable.c
	$(CC) -c HashTable.c -g

Dictionary.o:	Dictionary.h Dictionary.c HashTable.o
	$(CC) -c Dictionary.c -g

List.o: List.h
	$(CC) -c List.c -g

clean:
	rm -f prog3 Enrollment Enrollment.o HashTable.o Dictionary.o List.o

check:
	valgrind --leak-check=full ./prog3 < test.txt

