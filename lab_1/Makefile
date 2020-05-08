
TARGET = out
LIBS =
CFLAGS =
CC = gcc
all:
	$(CC) $(LIBS) $(CFLAGS) -c main.c -o main.o
	$(CC) -o $(TARGET) main.o $(LIBS) $(CFLAGS)
	strip $(TARGET)
	clear
clean:
	rm *.o 
	rm $(TARGET)
