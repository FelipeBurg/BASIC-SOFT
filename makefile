CC=gcc
CFLAGS=-Wall -Wextra -pedantic
LDFLAGS=-lrt

SRC=registers.c functions.c
OBJ=$(SRC:.c=.o)
TARGET=emulador/registers

all: directories $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

directories:
	mkdir -p emulador	

	registers.o: functions.h
	functions.o: functions.h	