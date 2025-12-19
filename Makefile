CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -std=c99
SRC = src/main.c src/ui.c src/time_logic.c
OBJ = $(SRC:.c=.o)
TARGET = timewatch

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

clean:
	rm -f src/*.o $(TARGET)
