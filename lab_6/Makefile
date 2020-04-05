TARGET = out
LIBS =
CFLAGS =
CC = gcc
all:
	clear
	$(CC) -c main.c -o main.o
	$(CC) -o $(TARGET) -g main.o
	strip $(TARGET)
clean:
	rm *.o 
	rm $(TARGET)
