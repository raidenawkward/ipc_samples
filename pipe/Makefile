
TAR := momsays

SRC := $(shell ls *.c)
OBJ := $(SRC:.c=.o)

all:$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TAR)
clean:
	rm -rf $(OBJ) $(TAR)
