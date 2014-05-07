
TAR_CLIENT := client
TAR_SERVER := server

SRC_CLIENT := $(shell ls client*.c)
SRC_SERVER := $(shell ls server*.c)


OBJ_CLIENT := $(SRC_CLIENT:.c=.o)
OBJ_SERVER := $(SRC_SERVER:.c=.o)

all:$(OBJ_CLIENT) $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -o $(TAR_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -o $(TAR_SERVER)
client:$(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -o $(TAR_CLIENT)
server:$(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -o $(TAR_SERVER)
clean:
	rm -rf $(TAR_CLIENT) $(TAR_SERVER) $(OBJ_CLIENT) $(OBJ_SERVER)
