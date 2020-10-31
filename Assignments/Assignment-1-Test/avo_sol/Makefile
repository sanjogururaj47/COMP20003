# define C compiler & flags
CC = gcc
CFLAGS = -Wall

# define libraries to be linked (for example -lm)
LIB = 


HDR = llist.h data.h utils.h
SRC = main.c llist.c data.c utils.c

# OBJ is the same as SRC, just sustitute ".c" with ".o"
OBJ     = $(SRC:.c=.o)

# the executable name
EXE = dict


$(EXE): $(HDR) $(OBJ) Makefile
	echo $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ) $(LIB)


clean: 
	rm -f $(OBJ) $(EXE)

$(OBJ): $(HDR)

