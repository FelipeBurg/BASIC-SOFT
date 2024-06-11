CC = gcc
CFLAGS = -Wall -Wextra -pedantic
LDFLAGS = -lrt
TARGET = registers
SRC = registers.c functions.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
