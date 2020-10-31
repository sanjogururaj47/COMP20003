all: map1 map2

map1: map1.o read.o KDTree.o
	gcc -o map1 map1.o read.o KDTree.o -lm
map1.o: map1.c read.h
	gcc -c -Wall map1.c
read.o: read.c read.h
	gcc -c -Wall read.c
KDTree.o: KDTree.c KDTree.o
	gcc -c -Wall KDTree.c

map2: map2.o read.o KDTree.o
	gcc -o map2 map2.o read.o KDTree.o -lm
map2.o: map2.c read.h
	gcc -c -Wall map2.c
read.o: read.c read.h
	gcc -c -Wall read.c
KDTree.o: KDTree.c KDTree.o
	gcc -c -Wall KDTree.c