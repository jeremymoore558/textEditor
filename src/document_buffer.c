#include <stdio.h>
#include <string.h>
#include "document_buffer.h"

// Return 1 for error
int write_buffer_to_txt(DocBuffer* doc_buf){
	FILE *fptr;
	if (doc_buf->filename[0] == '\0') {
		return 1;
	}
	fptr = fopen(doc_buf->filename, "w");
	for (int i=0; i<GAP_BUFFER_SIZE; i++){
		if (doc_buf->buffer[i] != '\0'){
			putc((int)doc_buf->buffer[i], fptr);
		}
	}
	fclose(fptr);
	return 0;
}

// Initialize DocBuffer struct by reading in from file.
void read_text_file(char* filename, DocBuffer* doc_buf){
	FILE *fptr;
	fptr = fopen(filename, "r");

	int c;
	while ((c = getc(fptr)) != EOF){
		doc_buf->buffer[doc_buf->cursor.left] = c;
		doc_buf->cursor.left += 1;
	}
	doc_buf->cursor.right = GAP_BUFFER_SIZE-1;

	strcpy(doc_buf->filename, filename);
	fclose(fptr);
}

void print_buffer(DocBuffer* doc_buf){
	//printf("\033[2J");
	//printf("\033[H");
	printf("\x1b[?25l");
	for (int i=0; i<GAP_BUFFER_SIZE; i++){
		switch (doc_buf->buffer[i]){
			case '\0':
				break;
			case '\n':
				printf("\r");
			default:
				printf("%c", doc_buf->buffer[i]);
		}

		if (i == doc_buf->cursor.left){
			printf("|");
		}
	}
	printf("\r\n");
}
