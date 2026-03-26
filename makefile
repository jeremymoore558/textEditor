CC = gcc
TARGET = a
CFLAGS = -Wall

$(TARGET): ./src/main.c ./src/document_buffer.c ./src/input_handler.c
	$(CC) ./src/main.c -o $(TARGET) $(CFLAGS)
