
TAR_PUBLISHER := publisher
TAR_READER := reader

CFLAGS += -g

SRC_PUBLISHER := $(shell ls publisher*.c)
SRC_READER := $(shell ls reader*.c)


OBJ_PUBLISHER := $(SRC_PUBLISHER:.c=.o)
OBJ_READER := $(SRC_READER:.c=.o)

all:$(OBJ_PUBLISHER) $(OBJ_READER)
	$(CC) $(CFLAGS) $(OBJ_PUBLISHER) -o $(TAR_PUBLISHER)
	$(CC) $(CFLAGS) $(OBJ_READER) -o $(TAR_READER)
client:$(OBJ_PUBLISHER)
	$(CC) $(CFLAGS) $(OBJ_PUBLISHER) -o $(TAR_PUBLISHER)
server:$(OBJ_READER)
	$(CC) $(CFLAGS) $(OBJ_READER) -o $(TAR_READER)
clean:
	rm -rf $(TAR_PUBLISHER) $(TAR_READER) $(OBJ_PUBLISHER) $(OBJ_READER)
