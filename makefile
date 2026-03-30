CC = gcc
CFLAGS = -Wall

all: main.o document_buffer.o input_handler.o insert_mode.o a

main.o: ./src/main.c ./src/main.h
	$(CC) -c ./src/main.c -o ./build/main.o

document_buffer.o: ./src/document_buffer.c ./src/document_buffer.h
	$(CC) -c ./src/document_buffer.c -o ./build/document_buffer.o

input_handler.o: ./src/input_handler.c ./src/input_handler.h
	$(CC) -c ./src/input_handler.c -o ./build/input_handler.o

insert_mode.o: ./src/insert_mode.c ./src/insert_mode.h
	$(CC) -c ./src/insert_mode.c -o ./build/insert_mode.o

a: ./build/main.o ./build/document_buffer.o ./build/input_handler.o ./build/insert_mode.o
	$(CC) -o ./bin/a ./build/main.o ./build/document_buffer.o ./build/input_handler.o ./build/insert_mode.o
