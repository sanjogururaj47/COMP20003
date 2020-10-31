dict: list.o dict.o read.o
	gcc -o dict list.o dict.o read.o
list.o: list.c list.h
	gcc -c -Wall list.c
dict.o: dict.c list.h
	gcc -c -Wall dict.c
read.o: read.c read.h
	gcc -c -Wall read.c
