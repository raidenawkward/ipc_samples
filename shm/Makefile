TAR := b
SRC := $(shell ls *.c)
OBJ := $(SRC:.c=.o)

CFLAGS += -g

all:$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TAR)
clean:
	rm -rf $(OBJ) $(TAR)
