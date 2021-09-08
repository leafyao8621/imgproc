CC = gcc
SRC = src/main.c $(wildcard src/*/*.c)
OBJ = $(SRC:.c=.o)
BIN = test

%.o: %.c
	$(CC) -g -c $< -o $@

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) -lpng

.PHONY: clean
clean:
	@rm $(OBJ)
	@rm $(BIN)
